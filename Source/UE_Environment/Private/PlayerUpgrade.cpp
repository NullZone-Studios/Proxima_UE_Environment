// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUpgrade.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UPlayerUpgrade::UPlayerUpgrade()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UPlayerUpgrade::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerUpgrade::ApplyUpgrade() {
	TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter) {
		// Example upgrade: Increase player's max health by 20%
		
	}
}
