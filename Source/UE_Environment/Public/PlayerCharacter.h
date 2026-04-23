// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE_ENVIRONMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Health")
	float HealthRegeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Defense")
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Movement")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float CriticalChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Base Stats|Combat")
	float Haste;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float XP_Gain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float XP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float NextLevelXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Progression")
	float LevelUpMultiplier;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
