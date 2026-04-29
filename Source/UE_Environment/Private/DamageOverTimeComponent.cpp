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
		}

		if (!Dot->IsActive())
		{
			ActiveDOTEffects.RemoveAtSwap(i);
		}
	}
}

void UDamageOverTimeComponent::AddDamageOverTime(float TotalDamage, float Duration)
{
		if (Duration <= 0.f || TotalDamage <= 0.f)
		{
			return;
		}

		UFDamageOverTimeEffect* NewDot = NewObject<UFDamageOverTimeEffect>(this);
		NewDot->TotalDamage = TotalDamage;
		NewDot->Duration = Duration;
		NewDot->TimeRemaining = Duration;
		NewDot->DamagePerSecond = TotalDamage / Duration;
		ActiveDOTEffects.Add(NewDot);
}

