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
		return true;
	}
	else {
		return false;
	}
}

bool ABaseEnemy::IsAlive() const
{
	return Health >= 0;
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
	return InvulnerabilityTimer >= 0;
}

