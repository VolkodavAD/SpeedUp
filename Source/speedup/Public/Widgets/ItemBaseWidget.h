// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Items/Item.h"
#include "ItemBaseWidget.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SPEEDUP_API UItemBaseWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void SetItemName(FString ItemName);

	UFUNCTION(BlueprintCallable)
		void SetNFTtype(ItemType ItemType);

	UFUNCTION(BlueprintCallable)
		void SetNFTrare(ItemLevelRarity ItemRare);

	UFUNCTION(BlueprintCallable)
		void SetNFTactiveStatus(StatusItem ItemStatus);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NFTnameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* NFTimageBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NFTtypeTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NFTlevelRareTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NFTactiveStatusTextBlock;

	int NFTmaxPower;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* NFTcurrentPower;

	/*UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* TimeToPowerRecovery;*/

protected:

	void NativeOnInitialized() override;
};
