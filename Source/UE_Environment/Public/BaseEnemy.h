// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageEntity.h"
#include <DamageOverTimeComponent.h>
#include "BaseEnemy.generated.h"

UCLASS()
class UE_ENVIRONMENT_API ABaseEnemy : public ACharacter, public IDamageEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	UDamageOverTimeComponent* DamageOverTimeComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Health")
	float HealthRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float InvulnerabilityDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Stats|Base Stats|Combat")
	float InvulnerabilityTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float XPReward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Stats|Base Stats|Combat")
	float HealthRegenDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Stats|Base Stats|Combat")
	float HealthRegenDelayTimer;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Inherited via IDamageEntity
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool TakeDamage(float DamageAmount, bool invulnerable, bool CircumventInvulnerability) override;
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsAlive() const override;
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetDefenseCalculation() const override;
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void RegenerateHealth(float DeltaTime);


	// Inherited via IDamageEntity
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ResetInvulnerability() override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ResetTempInvulnerability(float TempInvulnerabilityDuration) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void UpdateInvulnerability(float DeltaTime) override;

	// Inherited via IDamageEntity
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsInvulnerable() const override;
};
