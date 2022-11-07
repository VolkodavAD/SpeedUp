// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "Misc/DateTime.h"
#include "GeoData/Speedup_GeoDataSystem.h"

UItemManager::UItemManager()
{}
// Called when the game starts
void UItemManager::BeginPlay()
{
	Super::BeginPlay();
	//PostFromBack_SlotsStats();
	//PostFromBack_AllItems();

	PostFromBack_SlotsStats();
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
	//UItem* FindedItems;
	for (int i = 0; i < MyItems.Num(); i++)
	{
		if (MyItems[i]->GetItemInfo().ItemID == ItemID)
		{
			return MyItems[i];
			//return FindedItems;
		}
	}
	return nullptr;
}

void UItemManager::UpdateLastPathID(int ItemID, int PathID)
{
	GetMyItem(ItemID)->UpdateLastPathID(PathID);
}

bool UItemManager::ActivateItem(int ItemID, int PathID, int SlotID, int& ErrorID)
{
	if (ItemsSlot.Num() <= SlotID)
	return false;

	if (!ItemsSlot[SlotID].IsUnlock)
	return false;

	//if (ItemsSlot[SlotID].ItemID > 0)
	//return false;

	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr) { return false; }

	if (ItemByID->Energy > 0) {

		int l_ItemEnergy = GetMyItem(ItemID)->Energy = ItemByID->Energy - 1;
	}
	ItemByID->SetItemStatus(StatusItem::Active);

	ItemsSlot[SlotID].ItemID = ItemID;
	ItemsSlot[SlotID].PathForItem = PathID;

	UpdateLastPathID(ItemID, PathID);

	return true;
}

bool UItemManager::DeactivateItem(int ItemID, int SlotID, int& ErrorID)
{
	if (!ItemsSlot[SlotID].IsUnlock)
		return false;

	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr) { return false; }

	ItemByID->SetItemStatus(StatusItem::Deactive);

	ItemsSlot[SlotID].ItemID = -1;
	ItemsSlot[SlotID].PathForItem = -1;

	return true;
}

bool UItemManager::UpdateItem(int ItemID, int SlotID, int& ErrorID)
{
	return true;
}

//----------------------------------- ЗАГЛУШКИ ПО БЭКУ ---------------------------------------

//получаем состояние слотов из бэка
void UItemManager::PostFromBack_SlotsStats()
{
	FItemSlot AddedSlot;
	AddedSlot.IsUnlock = true;
	AddedSlot.ItemID = -1;
	AddedSlot.Items_TimerHandle = Items_TimerHandle;
	ItemsSlot.Add(AddedSlot);

	AddedSlot.IsUnlock = false;
	ItemsSlot.Add(AddedSlot);
	ItemsSlot.Add(AddedSlot);
}

//получаем все предметы из бека, тут же проверяем есть ли активные
void UItemManager::PostFromBack_AllItems()
{
	/*
	UItem* AddedItem = NewObject<UItem>();
	FBaseItemInfo AddedItemInfi;
	AddedItemInfi.ItemID = 1;
	AddedItemInfi.ItemLevel = 1;
	AddedItemInfi.ItemName = "Snikers";
	AddedItemInfi.ItemStatus = StatusItem::Deactive;
	AddedItemInfi.ItemRarity = ItemLevelRarity::Common;
	AddedItemInfi.Type = ItemType::Sneakers;
	AddedItem->SetItemInfo(AddedItemInfi);
	AddedItem->Energy = 3;
	
	MyItems.Add(AddedItem);
	*/
}

void UItemManager::AddItem(UItem* AddedItem)
{
	MyItems.Add(AddedItem);
}

void UItemManager::ClearItemArray()
{
	MyItems.Empty(0);
}