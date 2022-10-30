// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Widgets/BaseSpeedUpWidget.h"
#include "PointInfoWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class SPEEDUP_API UPointInfoWidget : public UBaseSpeedUpWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PointTD;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* PointLocation;
};
