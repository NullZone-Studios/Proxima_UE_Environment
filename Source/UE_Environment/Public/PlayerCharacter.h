// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Engine/Texture2D.h>
#include "DamageEntity.h"
#include "DamageOverTimeComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXPGained, float, Amount);

UCLASS()
class UE_ENVIRONMENT_API APlayerCharacter : public ACharacter, public IDamageEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Damage", meta = (AllowPrivateAccess = "true"))
	UDamageOverTimeComponent* DamageOverTimeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components|Movement")
	TSubclassOf<UActorComponent> PlayerMovementComponentClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Movement", meta = (AllowPrivateAccess = "true"))
	class UActorComponent* PlayerMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float HealthRegeneration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float AttackSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Defense")
	float Defense = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Movement")
	float BaseMovementSpeed = 300.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Movement")
	float TrueMovementSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Movement")
	float SprintModifier = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float CriticalChance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float CriticalDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Duration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Range = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Haste = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float XP_Gain = 1.0F;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float XP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float NextLevelXP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	int32 Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float LevelUpMultiplier = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float BaseAttackCooldown = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float BaseAbility1Cooldown = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float BaseAbility2Cooldown = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float BaseAbility3Cooldown = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float TrueAttackCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float TrueAbility1Cooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float TrueAbility2Cooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float TrueAbility3Cooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float AttackCooldownTimer = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float Ability1CooldownTimer = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float Ability2CooldownTimer = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float Ability3CooldownTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float InvulnerabilityDuration = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float InvulnerabilityTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Cooldowns")
	float HealthRegenDelay = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats|Cooldowns")
	float HealthRegenDelayTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images|Attack")
	UTexture2D* AttackImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images|Abilities")
	UTexture2D* Ability1Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images|Abilities")
	UTexture2D* Ability2Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images|Abilities")
	UTexture2D* Ability3Image;

	UPROPERTY(BlueprintAssignable)
	FOnXPGained OnXPGained;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void UpdateCooldowns(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void UpdateCooldownStats();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void RegenerateHealth(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetAttackCooldown();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetAbility1Cooldown();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetAbility2Cooldown();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetAbility3Cooldown();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual bool IsAttackOffCooldown() const;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual bool IsAbility1OffCooldown() const;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual bool IsAbility2OffCooldown() const;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual bool IsAbility3OffCooldown() const;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual bool IsInvulnerable() const;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetInvulnerability();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void ResetTempInvulnerability(float TempInvulnerabilityDuration);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual void UpdateInvulnerability(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	virtual float GetNormalizedAttackSpeed() const;

	// Inherited via IDamageEntity
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool TakeDamage(float DamageAmount, bool invulnerable, bool CircumventInvulnerability) override;
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsAlive() const override;
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetDefenseCalculation() const override;
	UFUNCTION(BlueprintCallable, Category = "XP")
	void GainXP(float Amount);
};
