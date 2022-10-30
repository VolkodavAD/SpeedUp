// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

UItem::UItem()
{
}


void UItem::SetItemInfo(FBaseItemInfo NewItemInfo)
{
	ItemInfo.ItemID = NewItemInfo.ItemID;
	ItemInfo.ItemName = NewItemInfo.ItemName;
	ItemInfo.ItemLevel = NewItemInfo.ItemLevel;
	ItemInfo.ItemRarity = NewItemInfo.ItemRarity;
	ItemInfo.Type = NewItemInfo.Type;
	ItemInfo.ItemStatus = NewItemInfo.ItemStatus;
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

void UItem::SetItemStatus(StatusItem NewItemStatus)
{
	ItemInfo.ItemStatus = NewItemStatus;
}