#pragma once

#include "CoreMinimal.h"
#include "PlayerStatType.generated.h"

UENUM(BlueprintType)
enum class EPlayerStatType : uint8
{
	MaxHealth UMETA(DisplayName = "Max Health"),
	HealthRegeneration UMETA(DisplayName = "Health Regeneration"),
	Damage UMETA(DisplayName = "Damage"),
	AttackSpeed UMETA(DisplayName = "Attack Speed"),
	Haste UMETA(DisplayName = "Haste"),
	XP_Gain UMETA(DisplayName = "XP Gain"),
	Defense UMETA(DisplayName = "Defense"),
	MovementSpeed UMETA(DisplayName = "Movement Speed"),
	Range UMETA(DisplayName = "Range"),
	Duration UMETA(DisplayName = "Duration"),
	CriticalChance UMETA(DisplayName = "Critical Chance"),
	CriticalDamage UMETA(DisplayName = "Critical Damage"),
	MAX UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(EPlayerStatType, EPlayerStatType::MAX)