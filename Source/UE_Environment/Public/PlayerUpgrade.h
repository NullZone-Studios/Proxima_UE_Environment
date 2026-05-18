// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinorCardUpgrade.h"
#include "MinorCardDefinition.h"
#include "UpgradeChoiceType.h"
#include "PlayerStatType.h"
#include "PlayerUpgrade.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_ENVIRONMENT_API UPlayerUpgrade : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerUpgrade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Player Upgrade")
	TArray<FMinorCardUpgrade> MinorCards;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Upgrade|Minor Cards")
	TArray<TObjectPtr<UMinorCardDefinition>> MinorCardPool;

	UFUNCTION(BlueprintCallable, Category = "Player Upgrade|Minor Cards")
	void LoadMinorCardDefinitions();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DamageUpgrade = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DefenseUpgrade = 0.0f;

private:

	bool bMinorCardsLoaded = false;

	void OnMinorCardDefinitionsLoaded();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Player Upgrade")
	TArray<FMinorCardUpgrade> GenerateMinorCardChoices(int32 Amount = 3);

	UFUNCTION(BlueprintCallable, Category = "Player Upgrade")
	void PickMinorCard(const FMinorCardUpgrade& ChosenCard);

	UFUNCTION(BlueprintCallable, Category = "Player Upgrade")
	virtual void ApplyUpgrade();

	UFUNCTION(BlueprintCallable, Category = "Player Upgrade")
	virtual TArray<FMinorCardUpgrade> NextUpgrade(int64 Level);

	UFUNCTION(BlueprintPure, Category = "Player Upgrade")
	EUpgradeChoiceType GetUpgradeTypeForLevel(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Player Upgrade")
	bool AreMinorCardsLoaded() const { return bMinorCardsLoaded; }
};
