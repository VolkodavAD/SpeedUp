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
	//UItemManager* NFTItemManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UItemManager* NFTItemManager;
	//class USkeletalMeshComponent* MeshBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpeedup_GeoDataSystem* GeoDataSystemCPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBaseWalletWidget* WalletBaseClass;


public:

	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void ActiveItem(int ItemID, int SlotID, int PathID);
	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void DeactiveItem(int ItemID, int SlotID, int PathID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void UpdateItem(int ItemID, int PathID, float Distance, float Speed);
	void UpdateItem_Implementation(int ItemID, int PathID, float Distance, float Speed);

	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void ActiveSlot();
	//FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }
	//UFUNCTION(BlueprintNativeEvent, Category = "mesh")
	FORCEINLINE class UItemManager* GetNFTItemManager() const { return NFTItemManager; }
	FORCEINLINE class USpeedup_GeoDataSystem* GetGeoDataSystemCPP() const { return GeoDataSystemCPP; }
	FORCEINLINE class UBaseWalletWidget* GetWalletInfo()const { return WalletBaseClass; }

};
