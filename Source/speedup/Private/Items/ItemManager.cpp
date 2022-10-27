// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "GeoData/Speedup_GeoDataSystem.h"

void UItemManager::InitItemManager()
{
	PostFromBack_SlotsStats();
	PostFromBack_AllItems();
}


void UItemManager::ActiveItem(int ItemID, int SlotID)
{

	for (int i = 0; i < MyItems.Num(); i++)
	{
		if (MyItems[ItemID]->GetItemID() == -1)
		{
			MyItems[ItemID]->SetItemStatus(StatusItem::Deactive);
		}
	}

	if (ItemsSlot[SlotID].IsUnlock)
	{
		ItemsSlot[SlotID].ItemID = ItemID;

		// получаем ID пути и запускаем его в компоненте
		Start_TimerItemCheck();
	}
}
void UItemManager::DeactiveItem(int ItemID, int SlotID)
{
	if (ItemsSlot[SlotID].IsUnlock)
	{
		ItemsSlot[SlotID].ItemID = -1;
		for (int i = 0; ItemsSlot.Num(); i++)
		{
		}
		Stop_TimerItemCheck();
	}
}

void UItemManager::Start_TimerItemCheck()
{
}
void UItemManager::Stop_TimerItemCheck()
{
}

//----------------------------------- ЗАГЛУШКИ ПО БЭКУ ---------------------------------------

//получаем состояние слотов из бэка
void UItemManager::PostFromBack_SlotsStats()
{
	ItemsSlot.Reset(3);
	ItemsSlot[0].IsUnlock = true;
	ItemsSlot[0].ItemID = -1;
	ItemsSlot[1].IsUnlock = false;
	ItemsSlot[2].IsUnlock = false;
}

//получаем все предметы из бека, тут же проверяем есть ли активные
void UItemManager::PostFromBack_AllItems()
{
	for (int i = 0; i < 4; i++)
	{
		UItem* AddedItem = NewObject<UItem>();
		FBaseItemInfo AddedItemInfi;
		AddedItemInfi.ItemID = i;
		AddedItemInfi.ItemLevel = 1;
		AddedItemInfi.ItemName = "TestSnikers";
		AddedItemInfi.ItemStatus = StatusItem::Deactive;
		AddedItemInfi.LevelRare = ItemLevelRare::Common;
		AddedItemInfi.Type = ItemType::Sneakers;
		AddedItem->SetItemInfo(AddedItemInfi);

		MyItems.Add(AddedItem);
	}
}

void UItemManager::PostFromBack_ActiveItem(int ItemID, int PathID)
{}
void UItemManager::PostFromBack_CheckActiveItem(int ItemID)
{}
void UItemManager::PostFromBack_DeactiveItem(int ItemID, int PathID)
{}