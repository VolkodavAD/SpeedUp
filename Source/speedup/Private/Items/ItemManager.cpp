// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "GeoData/Speedup_GeoDataSystem.h"

UItemManager::UItemManager()
{}
// Called when the game starts
void UItemManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UItemManager::InitItemManager()
{
	PostFromBack_SlotsStats();
	PostFromBack_AllItems();
}

UItem* UItemManager::GetMyItem(int ItemID)
{
	return MyItems[ItemID];
}

/*
FItemSlot UItemManager::GetItemSlot(int SlotID);
{
	return ItemsSlot[SlotID];
}*/

void UItemManager::Start_TimerItemCheck()
{
}

void UItemManager::Stop_TimerItemCheck()
{
}

bool UItemManager::ActiveItem(int ItemID, int SlotID, int& ErrorID)
{
	if (!ItemsSlot[SlotID].IsUnlock)
	return false;

	bool bTempFind = false;
	for (int i = 0; i < MyItems.Num(); i++)
	{
		if (MyItems[i]->GetItemID() == ItemID) bTempFind = true;
	}
	if (!bTempFind) return false;

	for (int i = 0; i < MyItems.Num(); i++)
	{
		if (MyItems[i]->GetItemID() == ItemID)
		{
			MyItems[i]->SetItemStatus(StatusItem::Active);
		}
	}

	if (ItemsSlot[SlotID].IsUnlock)
	{
		ItemsSlot[SlotID].ItemID = ItemID;

		// �������� ID ���� � ��������� ��� � ����������
		Start_TimerItemCheck();
	}
	return true;
}

bool UItemManager::DeactiveItem(int ItemID, int SlotID, int& ErrorID)
{
	if (!ItemsSlot[SlotID].IsUnlock)
		return false;

	for (int i = 0; i < MyItems.Num(); i++)
	{
		if (MyItems[i]->GetItemID() == ItemID)
		{
			MyItems[i]->SetItemStatus(StatusItem::Deactive);
		}
	}

	if (ItemsSlot[SlotID].IsUnlock)
	{
		ItemsSlot[SlotID].ItemID = -1;
		for (int i = 0; ItemsSlot.Num(); i++)
		{
		}
		Stop_TimerItemCheck();
	}
	return true;
}

//----------------------------------- �������� �� ���� ---------------------------------------

//�������� ��������� ������ �� ����
void UItemManager::PostFromBack_SlotsStats()
{
	ItemsSlot.Reset(3);
	ItemsSlot[0].IsUnlock = true;
	ItemsSlot[0].ItemID = -1;
	ItemsSlot[1].IsUnlock = false;
	ItemsSlot[2].IsUnlock = false;
}

//�������� ��� �������� �� ����, ��� �� ��������� ���� �� ��������
void UItemManager::PostFromBack_AllItems()
{
	UItem* AddedItem = NewObject<UItem>();
	FBaseItemInfo AddedItemInfi;
	AddedItemInfi.ItemID = 1;
	AddedItemInfi.ItemLevel = 1;
	AddedItemInfi.ItemName = "Snikers";
	AddedItemInfi.ItemStatus = StatusItem::Deactive;
	AddedItemInfi.LevelRare = ItemLevelRare::Common;
	AddedItemInfi.Type = ItemType::Sneakers;
	AddedItem->SetItemInfo(AddedItemInfi);
	AddedItem->MaxEnergy = 3;

	MyItems.Add(AddedItem);
}

void UItemManager::PostFromBack_ActiveItem(int ItemID, int PathID)
{}
void UItemManager::PostFromBack_CheckActiveItem(int ItemID)
{}
void UItemManager::PostFromBack_DeactiveItem(int ItemID, int PathID)
{}