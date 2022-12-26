// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GeoPath.h"
#include "SaveGeodate.generated.h"

/**
 * 
 */

UCLASS()
class SPEEDUP_API USaveGeodate : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool HaveSave;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FGeoLocationInfo LastPonitPath0;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FGeoLocationInfo LastPonitPath1;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FGeoLocationInfo LastPonitPath2;

	USaveGeodate();
};
