// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::UpdateCooldownStats() {
	TrueAttackCooldown = BaseAttackCooldown / (1 + Haste);
	TrueAbility1Cooldown = BaseAbility1Cooldown / (1 + Haste);
	TrueAbility2Cooldown = BaseAbility2Cooldown / (1 + Haste);
	TrueAbility3Cooldown = BaseAbility3Cooldown / (1 + Haste);
}

void APlayerCharacter::UpdateCooldowns(float DeltaTime) {
	if (this->AttackCooldown > 0) {
		this->AttackCooldown -= DeltaTime;
	}
	if (this->Ability1Cooldown > 0) {
		this->Ability1Cooldown -= DeltaTime;
	}
	if (this->Ability2Cooldown > 0) {
		this->Ability2Cooldown -= DeltaTime;
	}
	if (this->Ability3Cooldown > 0) {
		this->Ability3Cooldown -= DeltaTime;
	}
}

void APlayerCharacter::RegenerateHealth(float DeltaTime) {
	
	if (this->Health < this->MaxHealth) {
		this->Health += this->HealthRegeneration * DeltaTime;
		if (this->Health > this->MaxHealth) {
			this->Health = this->MaxHealth;
		}
	}
}


