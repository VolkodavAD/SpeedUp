// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpeedUpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "BaseWalletWidget.generated.h"


class UTextBlock;
class UScrollBox;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FWalletTransaction 
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		float earnedDKS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		float earnedInternalSPD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		FString dateTransaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int TransactionType;
	
};



UCLASS()
class SPEEDUP_API UBaseWalletWidget : public UBaseSpeedUpWidget
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable)
	//void RefreshSPDBalance();

public:
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* SPDBalance;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxReceiptHistory;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxSpendingHistory;

protected:

	void NativeOnInitialized() override;

};
