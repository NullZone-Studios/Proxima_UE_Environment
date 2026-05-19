// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageOverTimeComponent = CreateDefaultSubobject<UDamageOverTimeComponent>(TEXT("DamageOverTimeComponent"));

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<float> ABaseEnemy::CreateXPRewardArray(int MaxXPOrbAmount, float XPPerOrb)
{

	TArray<float> XPArray;

	while (XPReward > 0 && XPArray.Num() < MaxXPOrbAmount) {
		XPArray.Add(FMath::Min(XPReward, XPPerOrb));
		XPReward -= XPPerOrb;
	}

	if (XPReward > 0) {
		for (int i = 0; i < XPArray.Num(); i++) {
			if (XPArray[i] < XPPerOrb) {
				float NeededToFill = XPPerOrb - XPArray[i];
				float ToAdd = FMath::Min(NeededToFill, XPReward);
				XPArray[i] += ToAdd;
				XPReward -= ToAdd;
				if (XPReward <= 0) {
					break;
				}
			}
		}
	}

	return XPArray;
}

bool ABaseEnemy::TakeDamage(float DamageAmount, bool invulnerable, bool CircumventInvulnerability)
{
	if (!invulnerable || CircumventInvulnerability) {
		Health -= DamageAmount / GetDefenseCalculation();
		if (Health < 0) {
			Health = 0;
		}
		if (CircumventInvulnerability) {
			return false;
		}
		if (HealthRegen > 0 && HealthRegenDelay > 0) {
			HealthRegenDelayTimer = HealthRegenDelay;
		}
		return true;
	}
	else {
		return false;
	}
}

bool ABaseEnemy::IsAlive() const
{
	return Health > 0;
}

float ABaseEnemy::GetDefenseCalculation() const
{
	return (Defense / 100.0f) + 1;
}

void ABaseEnemy::ResetInvulnerability()
{
	InvulnerabilityTimer = InvulnerabilityDuration;
}

void ABaseEnemy::ResetTempInvulnerability(float TempInvulnerabilityDuration)
{
	if (TempInvulnerabilityDuration > this->InvulnerabilityTimer) {
		this->InvulnerabilityTimer = TempInvulnerabilityDuration;
	}
}

void ABaseEnemy::UpdateInvulnerability(float DeltaTime)
{
	if (this->InvulnerabilityTimer > 0) {
		this->InvulnerabilityTimer -= DeltaTime;
		if (this->InvulnerabilityTimer < 0) {
			this->InvulnerabilityTimer = 0;
		}
	}
}

bool ABaseEnemy::IsInvulnerable() const
{
	return InvulnerabilityTimer > 0;
}

void ABaseEnemy::RegenerateHealth(float DeltaTime) {
	if (this->HealthRegen <= 0 || this->HealthRegenDelay <= 0) {
		return;
	}

	if (this->HealthRegenDelayTimer > 0) {
		this->HealthRegenDelayTimer -= DeltaTime;
		return;
	}

	if (this->Health < this->MaxHealth) {
		this->Health += this->HealthRegen * DeltaTime;
		if (this->Health > this->MaxHealth) {
			this->Health = this->MaxHealth;
		}
	}
}

void ABaseEnemy::TakingDamage(FDamageInfo DamageInfo)
{
	OnTakingDamage.Broadcast(DamageInfo);
}

FDamageInfo ABaseEnemy::DealDamage() const
{
	float FinalDamage = this->AttackDamage;

	if (CriticalChance > 0) {
		float RandomValue = FMath::FRandRange(0.0f, 100.0f);
		if (RandomValue < CriticalChance) {
			FinalDamage *= (1 + CriticalDamage / 100.0f);
		}
	}

	if (FinalDamage < 0) {
		FinalDamage = 0;
	}

	FDamageInfo DamageInfo;
	DamageInfo.DamageAmount = FinalDamage;
	DamageInfo.IsCriticalHit = false;
	DamageInfo.CircumventInvulnerability = false;

	return DamageInfo;
}