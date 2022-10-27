// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/Item.h"
//#include "/Geodata/Geopath.h"
#include "..\..\Public\GeoData\GeoPath.h"
#include "TimerManager.h"
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
	UGeoPath* PathForItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	bool IsUnlock = false;
};

UCLASS()
class SPEEDUP_API UItemManager : public UObject
{
	GENERATED_BODY()

private:


	void InitItemManager();

	//�������� ��������� ������ �� �������
	void PostFromBack_SlotsStats();
	//�������� ��� �������� �� �������, ��� �� ��������� ���� �� ��������
	void PostFromBack_AllItems();

	//����������, ��������� � ������������ ������� �� �������
	void PostFromBack_ActiveItem(int ItemID, int PathID);
	void PostFromBack_CheckActiveItem(int ItemID);
	void PostFromBack_DeactiveItem(int ItemID, int PathID);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
	FTimerHandle Items_TimerHandle;

	void Start_TimerItemCheck();
	void Stop_TimerItemCheck();

public:
	//����� ��������� � ������ ��������� �� �������� ���������
	TArray<FItemSlot> ItemsSlot;
	TArray<UItem*> MyItems;

	void ActiveItem(int ItemID, int SlotID);
	void DeactiveItem(int ItemID, int SlotID);

};
