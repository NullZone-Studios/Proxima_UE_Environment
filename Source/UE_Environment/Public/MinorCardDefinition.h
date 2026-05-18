// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataAsset.h"
#include "PlayerStatType.h"
#include "MinorCardDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UE_ENVIRONMENT_API UMinorCardDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card")
	FText CardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card")
	TObjectPtr<UTexture2D> ShowcaseImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Upgrade")
	EPlayerStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Upgrade")
	float UpgradeAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Selection", meta = (ClampMin = "0.0"))
	float Weight = 1.0f;

	FPrimaryAssetId GetPrimaryAssetId() const;
};
