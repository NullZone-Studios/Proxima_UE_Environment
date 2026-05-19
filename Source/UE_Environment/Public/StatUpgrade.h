#pragma once

#include "CoreMinimal.h"
#include "PlayerStatType.h"
#include "EUpgradeMathType.h"
#include "StatUpgrade.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FStatUpgrade
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Upgrade")
	EPlayerStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Upgrade")
	EUpgradeMathType UpgradeMathType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Upgrade")
	float UpgradeAmount = 0.0f;

};