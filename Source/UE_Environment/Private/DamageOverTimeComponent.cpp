// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageOverTimeComponent.h"

// Sets default values for this component's properties
UDamageOverTimeComponent::UDamageOverTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageOverTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageOverTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (int32 i = ActiveDOTEffects.Num() - 1; i >= 0; --i)
	{
		UFDamageOverTimeEffect* Dot = ActiveDOTEffects[i];

		const float Damage = Dot->Tick(DeltaTime);

		if (Damage > 0.f)
		{
			UObject* Owner = GetOwner();
			if (IDamageEntity* DamageEntity = Cast<IDamageEntity>(Owner))
			{
				DamageEntity->TakeDamage(Damage, DamageEntity->IsInvulnerable(), true);
			}
		};

		if (!Dot->IsActive())
		{
			ActiveDOTEffects.RemoveAtSwap(i);
		};
	};
}

void UDamageOverTimeComponent::AddDamageOverTime(float TotalDamage, float Duration, EDamageOverTimeTypes DamageType)
{
	if (Duration <= 0.f || TotalDamage <= 0.f)
	{
		return;
	};

	EDOTStackingRules Rule = GetStackingRule(DamageType);

	for (UFDamageOverTimeEffect* Dot : ActiveDOTEffects)
	{
		if (Dot->DamageType == DamageType)
		{
			switch (Rule)
			{
			case EDOTStackingRules::RefreshExisting:
				Dot->TimeRemaining = Duration;
				return;

			case EDOTStackingRules::ReplaceExisting:
				Dot->TotalDamage = TotalDamage;
				Dot->Duration = Duration;
				Dot->TimeRemaining = Duration;
				Dot->DamagePerSecond = TotalDamage / Duration;
				return;

			case EDOTStackingRules::IgnoreNew:
				return;

			default:
				break;
			};
		};
	};

	int32 CurrentStacks = 0;

	for (const UFDamageOverTimeEffect* Dot : ActiveDOTEffects)
	{
		if (Dot->DamageType == DamageType)
		{
			CurrentStacks++;
		};
	};

	if (CurrentStacks >= GetMaxStacks(DamageType))
	{
		return;
	};

	UFDamageOverTimeEffect* NewDot = NewObject<UFDamageOverTimeEffect>(this);
	NewDot->TotalDamage = TotalDamage;
	NewDot->Duration = Duration;
	NewDot->TimeRemaining = Duration;
	NewDot->DamagePerSecond = TotalDamage / Duration;
	NewDot->DamageType = DamageType;
	ActiveDOTEffects.Add(NewDot);
}

EDOTStackingRules UDamageOverTimeComponent::GetStackingRule(EDamageOverTimeTypes Type)
{
	switch (Type)
	{
	case EDamageOverTimeTypes::Poison:
		return EDOTStackingRules::StackNew;

	case EDamageOverTimeTypes::Burn:
		return EDOTStackingRules::RefreshExisting;

	case EDamageOverTimeTypes::Bleed:
		return EDOTStackingRules::StackNew;

	case EDamageOverTimeTypes::Shock:
		return EDOTStackingRules::ReplaceExisting;
	default:
		return EDOTStackingRules::StackNew;
	};
}

int32 UDamageOverTimeComponent::GetMaxStacks(EDamageOverTimeTypes Type)
{
	switch (Type)
	{
	case EDamageOverTimeTypes::Poison:
		return 3;

	case EDamageOverTimeTypes::Burn:
		return 1;

	case EDamageOverTimeTypes::Bleed:
		return 5;

	case EDamageOverTimeTypes::Shock:
		return 1;

	default:
		return 1;
	};
}