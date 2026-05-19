#pragma once

#include "CoreMinimal.h"
#include "DamageInfo.h"
#include "DelegatesForGame.generated.h"


UDELEGATE()

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakingDamage, FDamageInfo, DamageInfo);