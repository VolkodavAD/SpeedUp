// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/NoExportTypes.h"
#include "Items/Item.h"
#include "TimerManager.h"
//#include "/Geodata/Geopath.h"
//#include "..\..\Public\GeoData\GeoPath.h"
//#include "TimerManager.h"
#include "ItemManager.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemSlot : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	//GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	int ItemID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	//UGeoPath* PathForItem;
	int PathForItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	bool IsUnlock = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	FTimerHandle Items_TimerHandle;
};

//UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPEEDUP_API UItemManager : public UActorComponent
{

	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemManager();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyBindableEvent);

private:
	void InitItemManager();

	//получаем состояние слотов из сервере
	void PostFromBack_SlotsStats();
	//получаем все предметы из сервере, тут же проверяем есть ли активные
	void PostFromBack_AllItems();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
	FTimerHandle Items_TimerHandle;


public:
	//слоты инвенторя и список имеющихся на аккаунте предметов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	TArray<FItemSlot> ItemsSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<UItem*> MyItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FItemStatistic> MyItemStatistic;

	UFUNCTION(BlueprintCallable)
	bool ActivateItem(int ItemID, int PathID, int SlotID, int& ErrorID);
	UFUNCTION(BlueprintCallable)
	bool DeactivateItem(int ItemID, int SlotID, int& ErrorID);
	UFUNCTION(BlueprintCallable)
	bool UpdateItem(int ItemID, int SlotID, int& ErrorID);

	UFUNCTION(BlueprintCallable)
	void UpdateLastPathID(int ItemID, int PathID);

	UFUNCTION(BlueprintCallable)
	UItem* GetMyItem(int ItemID);

	UFUNCTION(BlueprintCallable)
	void AddItem(UItem* AddedItem);

	UFUNCTION(BlueprintCallable)
	void ClearItemArray();
	//UFUNCTION(BlueprintCallable)
	//FItemSlot GetItemSlot(int SlotID);
};
