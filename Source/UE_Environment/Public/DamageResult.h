#pragma once

#include "CoreMinimal.h"
#include "DamageResult.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FDamageResult
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Result")
	float FinalDamageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Result")
	bool DidDamage;

};