#pragma once

#include "CoreMinimal.h"
#include "UpgradeChoiceType.generated.h"

UENUM(BlueprintType)
enum class EUpgradeChoiceType : uint8
{
	Minor,
	Major,
	Augment,
	Weapon
};