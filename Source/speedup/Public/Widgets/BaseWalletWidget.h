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
		FString earnedDKS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		FString earnedInternalSPD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		FDateTime dateTransaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int TransactionType;
	
};



UCLASS()
class SPEEDUP_API UBaseWalletWidget : public UBaseSpeedUpWidget
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable)
	//void RefreshSPDBalance();
private:
	UPROPERTY(VisibleAnywhere)
		FWalletTransaction WalletInfo;

public:
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* SPDBalance;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxReceiptHistory;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxSpendingHistory;

	UFUNCTION(BlueprintCallable)
		void SetWalletInfo(FWalletTransaction NewWalletInfo);

protected:

	void NativeOnInitialized() override;

};
