#pragma once

#include "CoreMinimal.h"
#include "EUpgradeMathType.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EUpgradeMathType : uint8
{
	Additive UMETA(DisplayName = "Additive"),
	Multiplicative UMETA(DisplayName = "Multiplicative"),
};