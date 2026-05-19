// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "StatUpgrade.h"
#include "MajorCardDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UE_ENVIRONMENT_API UMajorCardDefinition : public UPrimaryDataAsset
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
	TArray<FStatUpgrade> StatUpgrades;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Minor Card|Selection", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float Weight = 1.0f;

	FPrimaryAssetId GetPrimaryAssetId() const;
};
