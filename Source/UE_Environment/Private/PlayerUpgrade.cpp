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
		if (CardDefinition)
		{
			AvailableCards.Add(CardDefinition);
		}
	}

	const int32 CardsToGenerate = FMath::Min(Amount, AvailableCards.Num());

	for (int32 i = 0; i < CardsToGenerate; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, AvailableCards.Num() - 1);

		UMinorCardDefinition* SelectedDefinition = AvailableCards[RandomIndex];
		AvailableCards.RemoveAt(RandomIndex);

		FMinorCardUpgrade NewCard;
		NewCard.CardName = SelectedDefinition->CardName;
		NewCard.Description = SelectedDefinition->Description;
		NewCard.ShowcaseImage = SelectedDefinition->ShowcaseImage;
		NewCard.StatType = SelectedDefinition->StatType;
		NewCard.UpgradeAmount = SelectedDefinition->UpgradeAmount;

		GeneratedCards.Add(NewCard);
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

TArray<FMinorCardUpgrade> UPlayerUpgrade::NextUpgrade(int64 Level) {
	// Implementation for moving to the next upgrade
	
	if (!bMinorCardsLoaded || MinorCardPool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to generate upgrade before cards were loaded"));
		return TArray<FMinorCardUpgrade>();
	}

	TArray<FMinorCardUpgrade> Choices = GenerateMinorCardChoices(3);

	this->DamageUpgrade += (Level >= 20) ? 2.0f : 1.0f;
	this->DefenseUpgrade += (Level >= 20) ? 3.0f : 2.0f;
	
	return Choices;
}

EUpgradeChoiceType UPlayerUpgrade::GetUpgradeTypeForLevel(int32 Level) const
{
	return Level % 3 == 0
		? EUpgradeChoiceType::Major
		: EUpgradeChoiceType::Minor;
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