// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Items/ItemManager.h"
//#include "HTTPAPIComponent.h"
#include "GeoData/Speedup_GeoDataSystem.h"
#include "widgets/BaseWalletWidget.h"
#include "speedupGameModeBase.generated.h"

/**
 * 
 */


UCLASS()
class SPEEDUP_API AspeedupGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AspeedupGameModeBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UItemManager* NFTItemManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class USpeedup_GeoDataSystem* GeoDataSystemCPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBaseWalletWidget* WalletBaseClass;


public:

	//UFUNCTION(BlueprintCallable, Category = "GeoData")
	//void ActiveItem(int ItemID, int PathID, int SlotID);
	//UFUNCTION(BlueprintCallable, Category = "GeoData")
	//void DeactiveItem(int ItemID, int PathID, int SlotID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void UpdatePathItem(int ItemID, int SlotN, float Distance, float Speed);
	void UpdatePathItem_Implementation(int ItemID, int SlotN, float Distance, float Speed);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void FinalPathItem(int ItemID, int PathID, int SlotN, float Distance, float Speed);
	void FinalPathItem_Implementation(int ItemID, int PathID, int SlotN, float Distance, float Speed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void PostActivationItem(int ItemID, int PathID, int SlotID);
	void PostActivationItem_Implementation(int ItemID, int PathID, int SlotID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void PostDeactivationItem(int ItemID, int PathID, int SlotID);
	void PostDeactivationItem_Implementation(int ItemID, int PathID, int SlotID);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Popup")
	//void ShowPopup(const FString Message, const PopupType MessageType);
	//void ShowPopup_Implementation(const FString Message, const PopupType MessageType);

	UFUNCTION(BlueprintCallable, Category = "Slot")
	void ActiveSlot();

	UFUNCTION(BlueprintCallable, Category = "Widjet")
	void SetWalletInfo(UBaseWalletWidget* UBaseWalletWidget);


	FORCEINLINE class UItemManager* GetNFTItemManager() const { return NFTItemManager; }
//	FORCEINLINE class USpeedup_GeoDataSystem* GetGeoDataSystemCPP() const { return GeoDataSystemCPP; }
	FORCEINLINE UBaseWalletWidget* GetWalletInfo()const { return WalletBaseClass; }

};
