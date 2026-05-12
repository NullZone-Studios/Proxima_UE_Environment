// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageOverTimeComponent = CreateDefaultSubobject<UDamageOverTimeComponent>(TEXT("DamageOverTimeComponent"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->TargetArmLength = 1000.0f;
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f));
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(SpringArmComponent);
	PlayerCameraComponent->SetRelativeRotation(FRotator(-3.5f, -0.0f, 0.0f));

	PlayerUpgradeComponent = CreateDefaultSubobject<UPlayerUpgrade>(TEXT("PlayerUpgradeComponent"));

	Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	if (PlayerMovementComponentClass) {
		PlayerMovementComponent = NewObject<UActorComponent>(this, PlayerMovementComponentClass, TEXT("PlayerMovementComponent"));
		
		if (PlayerCameraComponent) {
			PlayerMovementComponent->RegisterComponent();
			AddInstanceComponent(PlayerMovementComponent);
		}
	}

	if (PlayerHUDClass && IsLocallyControlled()) {
		PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (PlayerHUD) {
			PlayerHUD->AddToViewport();
		}
	}

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
	TrueAttackCooldown = BaseAttackCooldown / (1 + TrueAttackSpeed / 100);
	TrueAbility1Cooldown = BaseAbility1Cooldown / (1 + TrueHaste / 100);
	TrueAbility2Cooldown = BaseAbility2Cooldown / (1 + TrueHaste / 100);
	TrueAbility3Cooldown = BaseAbility3Cooldown / (1 + TrueHaste / 100);
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
	if (this->TrueHealthRegeneration <= 0 || this->HealthRegenDelay <= 0) {
		return;
	}

	if (this->HealthRegenDelayTimer > 0) {
		this->HealthRegenDelayTimer -= DeltaTime;
		return;
	}
	
	if (this->Health < this->MaxHealth) {
		this->Health += this->TrueHealthRegeneration * DeltaTime;
		if (this->Health > this->TrueMaxHealth) {
			this->Health = this->TrueMaxHealth;
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

bool APlayerCharacter::IsAttackOffCooldown() const
{
	return AttackCooldownTimer <= 0;
}

bool APlayerCharacter::IsAbility1OffCooldown() const
{
	return Ability1CooldownTimer <= 0;
}

bool APlayerCharacter::IsAbility2OffCooldown() const
{
	return Ability2CooldownTimer <= 0;
}

bool APlayerCharacter::IsAbility3OffCooldown() const
{
	return Ability3CooldownTimer <= 0;
}

void APlayerCharacter::UpdateInvulnerability(float DeltaTime)
{
	if (this->InvulnerabilityTimer > 0) {
		this->InvulnerabilityTimer -= DeltaTime;
		if (this->InvulnerabilityTimer < 0) {
			this->InvulnerabilityTimer = 0;
		}
	}
}

float APlayerCharacter::GetNormalizedAttackSpeed() const
{
	return 1 / AttackSpeed;
}

bool APlayerCharacter::TakeDamage(float DamageAmount, bool invulnerable, bool CircumventInvulnerability)
{
	if (!invulnerable || CircumventInvulnerability) {
		Health -= DamageAmount / GetDefenseCalculation();
		if (Health < 0) {
			Health = 0;
		}
		if (CircumventInvulnerability) {
			return false;
		}
		if (TrueHealthRegeneration > 0 && HealthRegenDelay > 0) {
			HealthRegenDelayTimer = HealthRegenDelay;
		}
		return true;
	}
	else {
		return false;
	}
}

bool APlayerCharacter::IsAlive() const
{
	return Health > 0;
}


float APlayerCharacter::GetDefenseCalculation() const
{
	return ( TrueDefense / 100.0f ) + 1;
}

bool APlayerCharacter::IsInvulnerable() const
{
	return InvulnerabilityTimer > 0;
}

void APlayerCharacter::ResetInvulnerability()
{
	this->InvulnerabilityTimer = this->InvulnerabilityDuration;
}

void APlayerCharacter::ResetTempInvulnerability(float TempInvulnerabilityDuration)
{
	if (TempInvulnerabilityDuration > this->InvulnerabilityTimer) {
		this->InvulnerabilityTimer = TempInvulnerabilityDuration;
	}
}

void APlayerCharacter::GainXP(float Amount)
{
	XP += Amount * TrueXPGain;
	OnXPGained.Broadcast(Amount * TrueXPGain);
}

void APlayerCharacter::TakingDamage(float DamageAmount, bool bCircumventInvulnerability)
{
	OnTakingDamage.Broadcast(DamageAmount, bCircumventInvulnerability);
}
