// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "Misc/DateTime.h"
#include "GeoData/Speedup_GeoDataSystem.h"

// ErrorID = 504; - не найден слот 
// ErrorID = 404; - не найден предмет

UItemManager::UItemManager()
{
	/*
	FItemSlot AddedSlot;
	AddedSlot.IsUnlock = true;
	AddedSlot.ItemID = -1;
	AddedSlot.Items_TimerHandle = Items_TimerHandle;
	ItemsSlot.Add(AddedSlot);
	
	FItemSlot AddedSlot;
	AddedSlot.IsUnlock = false;
	AddedSlot.ItemID = -1;
	AddedSlot.Items_TimerHandle = Items_TimerHandle;
	*/
	//ItemsSlot.Add(AddedSlot);
	//ItemsSlot.Add(AddedSlot);
	//ItemsSlot.Add(AddedSlot); 
}
// Called when the game starts
void UItemManager::BeginPlay()
{
	Super::BeginPlay();
	//PostFromBack_SlotsStats();
	//PostFromBack_AllItems();

}

// Called every frame
void UItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UItemManager::InitItemManager(int SlotCount)
{
	ItemsSlot.Empty();
	FItemSlot AddedSlot;
	AddedSlot.IsUnlock = false;
	AddedSlot.ItemID = -1;
	AddedSlot.Items_TimerHandle = Items_TimerHandle;
	for (int i = 0; i < 3; i++)
	{
		//ItemsSlot[i].IsUnlock = false;
		//ItemsSlot[i].ItemID = -1;
		//ItemsSlot[i].Items_TimerHandle = Items_TimerHandle;
		ItemsSlot.Add(AddedSlot);
		if (i < SlotCount)
		{
			ItemsSlot[i].IsUnlock = true;
		}
	}

	//for (int i = 0; i < SlotCount; i++)
	//{
	//	ItemsSlot[i].IsUnlock = true;
	//}
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

//void UItemManager::UpdateLastPathID(int ItemID, int PathID)
//{
//	GetMyItem(ItemID)->UpdateLastPathID(PathID);
//}


bool UItemManager::CheckCanActivateItem(int ItemID, int SlotID, int& ErrorID)
{
	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr)
	{
		return false;
		ErrorID = 404;
	}

	if (ItemByID->GetItemInfo().capacity > 0)
	{
		return true;
	}
	return false;
}

bool UItemManager::CheckCanDeactivateItem(int ItemID, int SlotID, int& ErrorID)
{
	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr) { return false; }
	return true;
}

bool UItemManager::ActivateItem(int ItemID, int PathID, int SlotID, int& ErrorID)
{
	if (!ItemsSlot[SlotID].IsUnlock) return false;

	UItem* ItemByID = GetMyItem(ItemID);

	if (ItemByID == nullptr)
	{
		return false;
		ErrorID = 404;
	}

	ItemByID->SetItemStatus(StatusItem::Active);

	ItemsSlot[SlotID].ItemID = ItemID;
	ItemsSlot[SlotID].PathForItem = PathID;

	ItemByID->UpdateLastPathID(PathID);

	return true;
}

bool UItemManager::DeactivateItem(int ItemID, int SlotID, int& ErrorID)
{
	//if (!ItemsSlot[SlotID].IsUnlock)
	//	return false;

	UItem* ItemByID = GetMyItem(ItemID);
	if (ItemByID == nullptr) { return false; }

	ItemByID->SetItemStatus(StatusItem::Deactive);

	ItemsSlot[SlotID].ItemID = -1;
	ItemsSlot[SlotID].PathForItem = -1;
	ItemByID->DifCapacity();

	return true;
}

bool UItemManager::UpdateItem(int ItemID, int SlotID, int& ErrorID)
{
	return true;
}

void UItemManager::AddItem(UItem* AddedItem)
{
	MyItems.Add(AddedItem);
}

void UItemManager::ClearItemArray()
{
	MyItems.Empty(0);
}

int UItemManager::FindFreeSlot()
{
	//UItem* FindedItems;
	for (int i = 0; i < 3; i++)
	{
		if (ItemsSlot[i].IsUnlock && ItemsSlot[i].ItemID == -1)
		{
			return i;
			//return FindedItems;
		}
	}
	return 0;
}

bool UItemManager::ActiveSlot()
{
	for (int i = 0; i < 3; i++)
	{
		if (ItemsSlot[i].IsUnlock == false)
		{
			ItemsSlot[i].IsUnlock = true;
			return true;
		}

	}
	return false;
}

int UItemManager::FindSlotByItemID(int ItemID)
{
	for (int i = 0; i < 3; i++)
	{
		if (ItemsSlot[i].ItemID == ItemID)
		{
			return i;
		}
	}
	return -1;
}