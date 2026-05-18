#pragma once

#include "CoreMinimal.h"
#include "MinorCardUpgrade.h"
#include "MajorCardUpgrade.h"
#include "UpgradeChoiceType.h"
#include "FCardChoices.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE_ENVIRONMENT_API FCardChoices
{
    GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Choices")
	TArray<FMinorCardUpgrade> MinorCardChoices;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Choices")
	TArray<FMajorCardUpgrade> MajorCardChoices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Choices")
	EUpgradeChoiceType UpgradeType;

};