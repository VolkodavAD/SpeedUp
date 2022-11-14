// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

UItem::UItem()
{
}


void UItem::SetItemInfo(FBaseItemInfo NewItemInfo)
{
	ItemInfo = NewItemInfo;
	//ItemInfo.ItemID = NewItemInfo.ItemID;
	//ItemInfo.ItemName = NewItemInfo.ItemName;
	//ItemInfo.ItemLevel = NewItemInfo.ItemLevel;
	//ItemInfo.ItemRarity = NewItemInfo.ItemRarity;
	//ItemInfo.Type = NewItemInfo.Type;
	//ItemInfo.ItemStatus = NewItemInfo.ItemStatus;
}

void UItem::UpdateLastPathID(int PathID)
{
	ItemInfo.last_trip_id = PathID;
}

FBaseItemInfo UItem::GetItemInfo()
{
	return ItemInfo;
}

int UItem::GetItemID()
{
	return ItemInfo.ItemID;
}

ItemType UItem::GetType()
{
	return ItemInfo.Type;
}

void UItem::LevelUp()
{
	ItemInfo.ItemLevel++;
}

void UItem::DifCapacity()
{
	ItemInfo.capacity--;
}

void UItem::SetItemStatus(StatusItem NewItemStatus)
{
	ItemInfo.ItemStatus = NewItemStatus;
}