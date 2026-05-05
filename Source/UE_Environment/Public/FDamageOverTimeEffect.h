// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EDamageOverTimeTypes.h"
#include "FDamageOverTimeEffect.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FDamageOverTimeEffect
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeRemaining = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamagePerSecond = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDamageOverTimeTypes DamageType;

    bool IsActive() const
    {
        return TimeRemaining > 0.0f;
    }

    float Tick(float DeltaTime)
    {
        const float ActualDelta = FMath::Min(DeltaTime, TimeRemaining);

        const float DamageThisTick = DamagePerSecond * ActualDelta;

        TimeRemaining -= ActualDelta;

        return DamageThisTick;
    }
};
