// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EDOTStackingRules.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDOTStackingRules : uint8
{
    StackNew        UMETA(DisplayName = "Stack New"),        // Tilføj altid ny DoT
    RefreshExisting UMETA(DisplayName = "Refresh Existing"), // Reset duration på eksisterende DoT
    ReplaceExisting UMETA(DisplayName = "Replace Existing"), // Erstat eksisterende DoT
    IgnoreNew       UMETA(DisplayName = "Ignore New"),        // Hvis den allerede findes, gør intet
	IntensifyAndRefresh UMETA(DisplayName = "Intensify and Refresh") // Øg skaden og reset duration på eksisterende DoT
};
