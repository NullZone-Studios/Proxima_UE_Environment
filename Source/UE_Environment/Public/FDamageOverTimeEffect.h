// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "FDamageOverTimeEffect.generated.h"

/**
 * 
 */
UCLASS()
class UE_ENVIRONMENT_API UFDamageOverTimeEffect : public UStruct
{
	GENERATED_BODY()
	
public:
    UPROPERTY()
    float TotalDamage = 0.0f;

    UPROPERTY()
    float Duration = 1.0f;

    UPROPERTY()
    float TimeRemaining = 0.0f;

    UPROPERTY()
    float DamagePerSecond = 0.0f;

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
