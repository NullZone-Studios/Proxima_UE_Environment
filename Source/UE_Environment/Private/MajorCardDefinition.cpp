// Fill out your copyright notice in the Description page of Project Settings.


#include "MajorCardDefinition.h"

FPrimaryAssetId UMajorCardDefinition::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("MajorCardDefinition", GetFName());
}