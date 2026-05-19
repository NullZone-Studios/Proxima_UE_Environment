// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUpgrade.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UPlayerUpgrade::UPlayerUpgrade()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
	LoadMinorCardDefinitions();
	
}


// Called every frame
void UPlayerUpgrade::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FMinorCardUpgrade> UPlayerUpgrade::GenerateMinorCardChoices(int32 Amount)
{
	TArray<FMinorCardUpgrade> GeneratedCards;
	TArray<UMinorCardDefinition*> AvailableCards;

	for (UMinorCardDefinition* CardDefinition : MinorCardPool)
	{
		if (CardDefinition && CardDefinition->Weight > 0.0f)
		{
			AvailableCards.Add(CardDefinition);
		}
	}

	for (int32 i = 0; i < Amount && AvailableCards.Num() > 0; i++)
	{
		float TotalWeight = 0.0f;

		for (UMinorCardDefinition* CardDefinition : AvailableCards)
		{
			TotalWeight += CardDefinition->Weight;
		}

		if (TotalWeight <= 0.0f)
		{
			break;
		}

		const float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
		float CurrentWeight = 0.0f;

		int32 SelectedIndex = INDEX_NONE;

		for (int32 CardIndex = 0; CardIndex < AvailableCards.Num(); CardIndex++)
		{
			CurrentWeight += AvailableCards[CardIndex]->Weight;

			if (RandomValue <= CurrentWeight)
			{
				SelectedIndex = CardIndex;
				break;
			}
		}

		if (SelectedIndex == INDEX_NONE)
		{
			break;
		}

		UMinorCardDefinition* SelectedDefinition = AvailableCards[SelectedIndex];

		FMinorCardUpgrade NewCard;
		NewCard.CardName = SelectedDefinition->CardName;
		NewCard.Description = SelectedDefinition->Description;
		NewCard.ShowcaseImage = SelectedDefinition->ShowcaseImage;
		NewCard.StatType = SelectedDefinition->StatType;
		NewCard.UpgradeAmount = SelectedDefinition->UpgradeAmount;

		GeneratedCards.Add(NewCard);

		// Sikrer at samme kort ikke kan komme flere gange i samme selection.
		AvailableCards.RemoveAt(SelectedIndex);
	}

	return GeneratedCards;
}

void UPlayerUpgrade::PickMinorCard(const FMinorCardUpgrade& ChosenCard)
{
	MinorCards.Add(ChosenCard);
	ApplyUpgrade();
}

void UPlayerUpgrade::ApplyUpgrade() {
	TMap<EPlayerStatType, float> StatUpgrades;

	for (EPlayerStatType StatType : TEnumRange<EPlayerStatType>())
	{
		StatUpgrades.Add(StatType, 0.0f);
	}

	for (const FMinorCardUpgrade& MinorCard : MinorCards)
	{
		StatUpgrades[MinorCard.StatType] += MinorCard.UpgradeAmount;
	}

		// Implement for MajorCardUpgrade when that is added
		// Implement for AugmentUpgrade when that is added

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!PlayerCharacter)
	{
		return;
	}

		//Update the Calculations when the last upgrades are added
		PlayerCharacter->TrueMaxHealth = PlayerCharacter->MaxHealth + StatUpgrades[EPlayerStatType::MaxHealth];
		PlayerCharacter->TrueHealthRegeneration = PlayerCharacter->HealthRegeneration + StatUpgrades[EPlayerStatType::HealthRegeneration];
		PlayerCharacter->TrueDamage = PlayerCharacter->Damage + StatUpgrades[EPlayerStatType::Damage] + this->DamageUpgrade;
		PlayerCharacter->TrueDefense = PlayerCharacter->Defense + StatUpgrades[EPlayerStatType::Defense] + this->DefenseUpgrade;
		PlayerCharacter->TrueHaste = PlayerCharacter->Haste + StatUpgrades[EPlayerStatType::Haste];
		PlayerCharacter->TrueXPGain = PlayerCharacter->XP_Gain + StatUpgrades[EPlayerStatType::XP_Gain];
		PlayerCharacter->TrueAttackSpeed = PlayerCharacter->AttackSpeed + StatUpgrades[EPlayerStatType::AttackSpeed];
		PlayerCharacter->TrueMovementSpeed = PlayerCharacter->BaseMovementSpeed + StatUpgrades[EPlayerStatType::MovementSpeed];
		PlayerCharacter->TrueRange = PlayerCharacter->Range + StatUpgrades[EPlayerStatType::Range];
		PlayerCharacter->TrueDuration = PlayerCharacter->Duration + StatUpgrades[EPlayerStatType::Duration];
		PlayerCharacter->TrueCriticalChance = PlayerCharacter->CriticalChance + StatUpgrades[EPlayerStatType::CriticalChance];
		PlayerCharacter->TrueCriticalDamage = PlayerCharacter->CriticalDamage + StatUpgrades[EPlayerStatType::CriticalDamage];
}

FCardChoices UPlayerUpgrade::NextUpgrade(int64 Level) {
	// Implementation for moving to the next upgrade
	
	if (!bMinorCardsLoaded || MinorCardPool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to generate upgrade before cards were loaded"));
		return FCardChoices();
	}

	FCardChoices CardChoices; //Remove ResolveUpgradeTypeForRuntime when the special types are implemented, and replace with GetUpgradeTypeForLevel directly
	CardChoices.UpgradeType = ResolveUpgradeTypeForRuntime(GetUpgradeTypeForLevel(Level));

	switch (CardChoices.UpgradeType)
	{
	case EUpgradeChoiceType::Minor:
		CardChoices.MinorCardChoices = GenerateMinorCardChoices(3);
		break;
	case EUpgradeChoiceType::Major:
		//Generate Major Card Choices when that is added
		break;
	default:
		break;
	}

	this->DamageUpgrade += (Level >= 20) ? 2.0f : 1.0f;
	this->DefenseUpgrade += (Level >= 20) ? 3.0f : 2.0f;

	return CardChoices;
}

EUpgradeChoiceType UPlayerUpgrade::GetUpgradeTypeForLevel(int32 Level) const
{
	if (Level <= 0)
	{
		return EUpgradeChoiceType::Minor;
	}

	// Special unlockable milestone
	if (Level == 10)
	{
		return EUpgradeChoiceType::SkillpointAndAugment;
	}

	// Fixed milestone
	if (Level == 20)
	{
		return EUpgradeChoiceType::Augment;
	}

	// Before level 20: every 3rd level is Major, otherwise Skillpoint
	if (Level < 20)
	{
		return Level % 3 == 0
			? EUpgradeChoiceType::Major
			: EUpgradeChoiceType::Skillpoint;
	}

	// Level 21+: Major, Minor, Minor repeat
	return Level % 3 == 0
		? EUpgradeChoiceType::Major
		: EUpgradeChoiceType::Minor;
}

EUpgradeChoiceType UPlayerUpgrade::ResolveUpgradeTypeForRuntime(EUpgradeChoiceType Type) const
{
	switch (Type)
	{
	case EUpgradeChoiceType::Skillpoint:
		return EUpgradeChoiceType::Minor;

	case EUpgradeChoiceType::Augment:
		return EUpgradeChoiceType::Major; // Temporary fallback

	case EUpgradeChoiceType::SkillpointAndAugment:
		return EUpgradeChoiceType::Minor; // Until both systems exist

	default:
		return Type;
	}
}

void UPlayerUpgrade::LoadMinorCardDefinitions()
{
	bMinorCardsLoaded = false;

	MinorCardPool.Empty();

	UAssetManager& AssetManager = UAssetManager::Get();

	TArray<FPrimaryAssetId> AssetIds;
	AssetManager.GetPrimaryAssetIdList(
		FPrimaryAssetType(TEXT("MinorCardDefinition")),
		AssetIds
	);

	UE_LOG(LogTemp, Warning, TEXT("Found %d MinorCardDefinition assets"), AssetIds.Num());

	if (AssetIds.Num() == 0)
	{
		return;
	}

	AssetManager.LoadPrimaryAssets(
		AssetIds,
		TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UPlayerUpgrade::OnMinorCardDefinitionsLoaded)
	);

}

void UPlayerUpgrade::OnMinorCardDefinitionsLoaded()
{
	MinorCardPool.Empty();

	UAssetManager& AssetManager = UAssetManager::Get();

	TArray<FPrimaryAssetId> AssetIds;
	AssetManager.GetPrimaryAssetIdList(
		FPrimaryAssetType(TEXT("MinorCardDefinition")),
		AssetIds
	);

	for (const FPrimaryAssetId& AssetId : AssetIds)
	{
		UObject* LoadedObject = AssetManager.GetPrimaryAssetObject(AssetId);
		UMinorCardDefinition* CardDefinition = Cast<UMinorCardDefinition>(LoadedObject);

		if (CardDefinition)
		{
			MinorCardPool.Add(CardDefinition);
			UE_LOG(LogTemp, Warning, TEXT("Loaded card: %s"), *CardDefinition->CardName.ToString());
		}
	}

	bMinorCardsLoaded = true;

	UE_LOG(LogTemp, Warning, TEXT("Loaded %d Minor Card Definitions"), MinorCardPool.Num());
}