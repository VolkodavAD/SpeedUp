// Fill out your copyright notice in the Description page of Project Settings.

#include "speedupGameModeBase.h"
#include "Components/ActorComponent.h"

AspeedupGameModeBase::AspeedupGameModeBase()
{
	NFTItemManager = CreateDefaultSubobject<UItemManager>(TEXT("ItemManager"));
	GeoDataSystemCPP = CreateDefaultSubobject<USpeedup_GeoDataSystem>(TEXT("GeoDataSystemCPP"));
}


void AspeedupGameModeBase::ActiveItem(int ItemID, int SlotID, int PathID)
{
	int ERR = 0;
	GetNFTItemManager()->ActivateItem(ItemID, SlotID, PathID, ERR);
	GetGeoDataSystemCPP()->StartTrackPath(PathID);
}


void AspeedupGameModeBase::DeactiveItem(int ItemID, int SlotID, int PathID)
{
	int ERR = 0;
	GetNFTItemManager()->DeactivateItem(ItemID, SlotID, ERR);
	GetGeoDataSystemCPP()->StopTrackPath(PathID);
}


void AspeedupGameModeBase::UpdateItem(int ItemID, int SlotID, int PathID)
{
	int ERR = 0;
	GetNFTItemManager()->UpdateItem(ItemID, SlotID, ERR);
	//GetGeoDataSystemCPP()->StopTrackPath(PathID);
}