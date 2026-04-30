// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FDamageOverTimeEffect.h"
#include "DamageEntity.h"
#include "EDamageOverTimeTypes.h"
#include "EDOTStackingRules.h"
#include "DamageOverTimeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_ENVIRONMENT_API UDamageOverTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageOverTimeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Over Time")
	TArray<UFDamageOverTimeEffect*> ActiveDOTEffects;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Damage Over Time")
	virtual void AddDamageOverTime(float TotalDamage, float Duration, EDamageOverTimeTypes DamageType);

	virtual int32 GetMaxStacks(EDamageOverTimeTypes Type);

	virtual EDOTStackingRules GetStackingRule(EDamageOverTimeTypes Type);
};
