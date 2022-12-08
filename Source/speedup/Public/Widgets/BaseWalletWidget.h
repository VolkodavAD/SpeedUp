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

UCLASS(Blueprintable)
class SPEEDUP_API UWalletTransaction : public UObject
{
	GENERATED_BODY()
		

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		float distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		float earnedDKS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		float earnedInternalSPD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		FString dateTransaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		int TransactionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WalletInfo")
		FString StampTime;
	UWalletTransaction();
};

/*UCLASS(Blueprintable)
class SPEEDUP_API UItem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		FBaseItemInfo ItemInfo;

	int TimeEnergyRestore = 0;

	UItem();

public:
	// For test is 3 variable is public.
	UPROPERTY(EditDefaultsOnly, Category = "ItemState")
		int MaxEnergy = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
		int Energy = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
		int CurrentTimeToEnergyRestore = 0;

	UFUNCTION(BlueprintCallable)
		void UpdateLastPathID(int PathID);
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	//UTexture2D* ItemImage;

	// image for review
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	//UTexture2D* ItemIcon;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	//StatusItem Status = StatusItem::Deactive;

	UFUNCTION(BlueprintCallable)
		void SetItemInfo(FBaseItemInfo NewItemInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FBaseItemInfo GetItemInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetItemID();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		ItemType GetType();

	UFUNCTION(BlueprintCallable)
		void LevelUp();

	UFUNCTION(BlueprintCallable)
		void SetItemActivStatus(StatusItem NewItemActivStatus);
};
*/

UCLASS(Blueprintable)
class SPEEDUP_API UBaseWalletWidget : public UObject
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable)
	//void RefreshSPDBalance();
private:
	UPROPERTY(VisibleAnywhere)
		UWalletTransaction* WalletInfo;

public:
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//UTextBlock* SPDBalance;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxReceiptHistory;

	//UPROPERTY(meta = (BindWidget))
	//UScrollBox* ScrollBoxSpendingHistory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wallet")
	TArray<UWalletTransaction*> MyHistory;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		UWalletTransaction* GetWalletHistoryInfo();

	UFUNCTION(BlueprintCallable)
		void SetWalletInfo(UWalletTransaction* NewWalletInfo);

	UFUNCTION(BlueprintCallable)
		void AddTransaction(UWalletTransaction* AddedTransaction);

protected:

	//void NativeOnInitialized() override;

};
