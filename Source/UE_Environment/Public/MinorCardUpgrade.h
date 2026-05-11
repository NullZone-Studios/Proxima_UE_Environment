#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "PlayerStatType.h"
#include "MinorCardUpgrade.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FMinorCardUpgrade
{
    GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Upgrade")
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Upgrade")
	EPlayerStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Upgrade")
	float UpgradeAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Upgrade")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Upgrade")
	TObjectPtr<UTexture2D> ShowcaseImage = nullptr;

};
