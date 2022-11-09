// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpeedUpWidget.h"
#include "Components/ActorComponent.h"
#include "UObject/NoExportTypes.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		int TransactionType;
	
};



UCLASS(Blueprintable)
class SPEEDUP_API UBaseWalletWidget : public UObject
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wallet")
	TArray<FWalletTransaction> MyHistory;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FWalletTransaction GetWalletHistoryInfo();

	UFUNCTION(BlueprintCallable)
		void SetWalletInfo(FWalletTransaction NewWalletInfo);

	UFUNCTION(BlueprintCallable)
		void AddTransaction(FWalletTransaction AddedTransaction);

protected:

	//void NativeOnInitialized() override;

};
