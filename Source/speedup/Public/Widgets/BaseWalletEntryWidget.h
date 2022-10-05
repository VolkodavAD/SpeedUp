// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpeedUpWidget.h"
#include "Components/TextBlock.h"
#include "BaseWalletEntryWidget.generated.h"

class TextBlock;
/**
 * 
 */
UCLASS()
class SPEEDUP_API UBaseWalletEntryWidget : public UBaseSpeedUpWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void HistoryDateUpdate();

	UFUNCTION(BlueprintCallable)
	void StepsWalkingCountUpdate();

	UFUNCTION(BlueprintCallable)
		void KmDayWalkingCountUpdate();

	UFUNCTION(BlueprintCallable)
		void SPDDayEarnedUpdate();

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlockDate;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlockStepsWalked;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlockKmWalked;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlockSPDEarned;

protected:

	void NativeOnInitialized() override;
};
