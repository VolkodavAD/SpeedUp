// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemManager.h"
#include "Misc/DateTime.h"
#include "GeoData/Speedup_GeoDataSystem.h"

// ErrorID = 504; - �� ������ ���� 
// ErrorID = 404; - �� ������ �������

UItemManager::UItemManager()
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

	return true;
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

	if (ItemByID->Energy > 0) 
	{
		int l_ItemEnergy = GetMyItem(ItemID)->Energy = ItemByID->Energy - 1;
	}
	else
	{
		return false;
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

	return true;
}

bool UItemManager::UpdateItem(int ItemID, int SlotID, int& ErrorID)
{
	return true;
}

//----------------------------------- �������� �� ���� ---------------------------------------

//�������� ��������� ������ �� ����
void UItemManager::PostFromBack_SlotsStats()
{
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