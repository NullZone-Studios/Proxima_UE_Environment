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
	TrueAttackCooldown = BaseAttackCooldown / (1 + AttackSpeed);
	TrueAbility1Cooldown = BaseAbility1Cooldown / (1 + Haste);
	TrueAbility2Cooldown = BaseAbility2Cooldown / (1 + Haste);
	TrueAbility3Cooldown = BaseAbility3Cooldown / (1 + Haste);
}

void APlayerCharacter::UpdateCooldowns(float DeltaTime) {
	if (this->AttackCooldownTimer > 0) {
		this->AttackCooldownTimer -= DeltaTime;
	}
	if (this->Ability1CooldownTimer > 0) {
		this->Ability1CooldownTimer -= DeltaTime;
	}
	if (this->Ability2CooldownTimer > 0) {
		this->Ability2CooldownTimer -= DeltaTime;
	}
	if (this->Ability3CooldownTimer > 0) {
		this->Ability3CooldownTimer -= DeltaTime;
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

void APlayerCharacter::ResetAttackCooldown(){
	this->AttackCooldownTimer = this->TrueAttackCooldown;
}
void APlayerCharacter::ResetAbility1Cooldown(){
	this->Ability1CooldownTimer = this->TrueAbility1Cooldown;
}
void APlayerCharacter::ResetAbility2Cooldown(){
	this->Ability2CooldownTimer = this->TrueAbility2Cooldown;
}
void APlayerCharacter::ResetAbility3Cooldown(){
	this->Ability3CooldownTimer = this->TrueAbility3Cooldown;
}




