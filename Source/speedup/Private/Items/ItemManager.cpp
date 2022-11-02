// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "GeoData/Speedup_GeoDataSystem.h"

UItemManager::UItemManager()
{}
// Called when the game starts
void UItemManager::BeginPlay()
{
	Super::BeginPlay();
	PostFromBack_SlotsStats();
	PostFromBack_AllItems();
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

bool UItemManager::ActivateItem(int ItemID, int SlotID, int PathID, int& ErrorID)
{
	if (!ItemsSlot[SlotID].IsUnlock)
	return false;

	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr) { return false; }

	if (ItemByID->Energy > 0) {

		int l_ItemEnergy = GetMyItem(ItemID)->Energy = ItemByID->Energy - 1;
	}
	ItemByID->SetItemStatus(StatusItem::Active);

	Start_TimerItemCheck();
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

	Stop_TimerItemCheck();

	return true;
}

//----------------------------------- �������� �� ���� ---------------------------------------

//�������� ��������� ������ �� ����
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

//�������� ��� �������� �� ����, ��� �� ��������� ���� �� ��������
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

void UItemManager::PostFromBack_ActiveItem(int ItemID, int PathID)
{
	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID->Energy > 0)
	{

		int l_ItemEnergy = GetMyItem(ItemID)->Energy = ItemByID->Energy - 1;
	}
	ItemByID->SetItemStatus(StatusItem::Active);

}
void UItemManager::PostFromBack_CheckActiveItem(int ItemID)
{}
void UItemManager::PostFromBack_DeactiveItem(int ItemID, int PathID)
{
	UItem* ItemByID = GetMyItem(ItemID);
	ItemByID->SetItemStatus(StatusItem::Deactive);
}

void UItemManager::AddItem(UItem* AddedItem)
{
	MyItems.Add(AddedItem);
}

void UItemManager::ClearItemArray()
{
	MyItems.Empty(0);
}