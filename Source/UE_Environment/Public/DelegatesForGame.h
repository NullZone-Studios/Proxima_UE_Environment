#pragma once

#include "CoreMinimal.h"
#include "DelegatesForGame.generated.h"


UDELEGATE()

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakingDamage, float, DamageAmount, bool, bCircumventInvulnerability);