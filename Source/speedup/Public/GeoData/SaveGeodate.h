// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
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
	FVector2D LastPonitPath0;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector2D LastPonitPath1;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector2D LastPonitPath2;

	USaveGeodate();
};
