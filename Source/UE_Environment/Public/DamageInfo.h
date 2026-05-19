#pragma once

#include "CoreMinimal.h"
#include "DamageInfo.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FDamageInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	float DamageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool IsCriticalHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	bool CircumventInvulnerability;

};