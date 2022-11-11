// Fill out your copyright notice in the Description page of Project Settings.

#include "speedupGameModeBase.h"
#include "Components/ActorComponent.h"

AspeedupGameModeBase::AspeedupGameModeBase()
{
	NFTItemManager = CreateDefaultSubobject<UItemManager>(TEXT("ItemManager"));
	GeoDataSystemCPP = CreateDefaultSubobject<USpeedup_GeoDataSystem>(TEXT("GeoDataSystemCPP"));
	WalletBaseClass = CreateDefaultSubobject<UBaseWalletWidget>(TEXT("WalletBaseClass"));
}


void AspeedupGameModeBase::ActiveItem(int ItemID, int SlotID, int PathID)
{
	int ERR = 0;
	bool result = GetNFTItemManager()->ActivateItem(ItemID, SlotID, PathID, ERR);
	if (result)
	{
		GetGeoDataSystemCPP()->StartTrackPath(SlotID, PathID, ItemID);
	}
}


void AspeedupGameModeBase::DeactiveItem(int ItemID, int SlotID, int PathID)
{
	int ERR = 0;
	bool result = GetNFTItemManager()->DeactivateItem(ItemID, SlotID, ERR);
	if (result)
	{
		GetGeoDataSystemCPP()->StopTrackPath(ItemID, PathID, SlotID);
	}
}


void AspeedupGameModeBase::UpdateItem_Implementation(int ItemID, int PathID, float Distance, float Speed)
{
	int ERR = 0;
}

void AspeedupGameModeBase::ActiveSlot()
{
	NFTItemManager->ActiveSlot();
}