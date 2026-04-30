#pragma once

#include "CoreMinimal.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakingDamage, float, DamageAmount, bool, bCircumventInvulnerability);