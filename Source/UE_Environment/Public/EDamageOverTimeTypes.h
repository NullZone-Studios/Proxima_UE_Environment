// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EDamageOverTimeTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDamageOverTimeTypes : uint8
{
	Poison UMETA(DisplayName = "Poison"),
	Burn   UMETA(DisplayName = "Burn"),
	Bleed  UMETA(DisplayName = "Bleed"),
	Shock  UMETA(DisplayName = "Shock")
};
