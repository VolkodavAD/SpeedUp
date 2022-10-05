// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemBaseWidget.h"

void UItemBaseWidget::NativeOnInitialized()
{
	FBaseItemInfo NewItemInfo;
	GetAndSetItemName(NewItemInfo.ItemName);
	GetAndSetNFTtype(NewItemInfo.Type);
	GetAndSetNFTrare(NewItemInfo.LevelRare);
	GetAndSetNFTactiveStatus(NewItemInfo.ItemStatus);
}

void UItemBaseWidget::GetAndSetItemName(FString NFTname)
{
	
	if (NFTnameTextBlock) {
		NFTnameTextBlock->SetText(FText::FromString(NFTname));
	}
}

void UItemBaseWidget::GetAndSetNFTtype(ItemType NFTtype)
{
	if (NFTtypeTextBlock) {
		NFTtypeTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTtype));
	}
}

void UItemBaseWidget::GetAndSetNFTrare(ItemLevelRare NFTrare)
{
	if (NFTlevelRareTextBlock) {
		NFTlevelRareTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTrare));
	}
}

void UItemBaseWidget::GetAndSetNFTactiveStatus(StatusItem NFTstatus)
{
	if (NFTactiveStatusTextBlock) {
		NFTactiveStatusTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTstatus));
	}
}