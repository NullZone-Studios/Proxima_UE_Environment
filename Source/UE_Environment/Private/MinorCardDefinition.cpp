// Fill out your copyright notice in the Description page of Project Settings.


#include "MinorCardDefinition.h"

FPrimaryAssetId UMinorCardDefinition::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("MinorCardDefinition", GetFName());
}