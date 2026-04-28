// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageEntity.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageEntity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_ENVIRONMENT_API IDamageEntity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool TakeDamage(float DamageAmount, bool invulnerable, bool CircumventInvulnerability) = 0;
	virtual bool IsAlive() const = 0;
	virtual void DamageOverTime(float DOTAmount, float DOTDuration) = 0;
};
