// Fill out your copyright notice in the Description page of Project Settings.

#include "speedupGameModeBase.h"
#include "Components/ActorComponent.h"

AspeedupGameModeBase::AspeedupGameModeBase()
{
	NFTItemManager = CreateDefaultSubobject<UItemManager>(TEXT("ItemManager"));
	//GeoDataSystemCPP = CreateDefaultSubobject<USpeedup_GeoDataSystem>(TEXT("GeoDataSystemCPP"));
	//WalletBaseClass = CreateDefaultSubobject<UBaseWalletWidget>(TEXT("CompWalletBaseClass"));
	WalletBaseClass = NewObject<UBaseWalletWidget>(UBaseWalletWidget::StaticClass());

}


//void AspeedupGameModeBase::ActiveItem(int ItemID, int PathID, int SlotID)
//{
//}
//
//void AspeedupGameModeBase::DeactiveItem(int ItemID, int PathID, int SlotID)
//{
//}

void AspeedupGameModeBase::UpdatePathItem_Implementation(int ItemID, int SlotN, float Distance, float Speed)
{
}

void AspeedupGameModeBase::FinalPathItem_Implementation(int ItemID, int PathID, int SlotN, float Distance, float Speed)
{
}

void AspeedupGameModeBase::PostActivationItem_Implementation(int ItemID, int PathID, int SlotID)
{}

void AspeedupGameModeBase::PostDeactivationItem_Implementation(int ItemID, int PathID, int SlotID)
{}

//void AspeedupGameModeBase::ShowPopup_Implementation(const FString Message, const PopupType MessageType)
//{}

void AspeedupGameModeBase::SetWalletInfo(UBaseWalletWidget* UBaseWalletWidget)
{
	WalletBaseClass = UBaseWalletWidget;
}

void AspeedupGameModeBase::ActiveSlot()
{
	NFTItemManager->ActiveSlot();
}