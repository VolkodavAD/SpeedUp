// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemBaseWidget.h"

void UItemBaseWidget::NativeOnInitialized()
{
	FBaseItemInfo NewItemInfo;
	SetItemName(NewItemInfo.ItemName);
	SetNFTtype(NewItemInfo.Type);
	SetNFTrare(NewItemInfo.ItemRarity);
	SetNFTactiveStatus(NewItemInfo.ItemActivStatus);
}

void UItemBaseWidget::SetItemName(FString NFTname)
{
	
	if (NFTnameTextBlock) {
		NFTnameTextBlock->SetText(FText::FromString(NFTname));
	}
}

void UItemBaseWidget::SetNFTtype(ItemType NFTtype)
{
	if (NFTtypeTextBlock) {
		NFTtypeTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTtype));
	}
}

void UItemBaseWidget::SetNFTrare(ItemLevelRarity NFTrare)
{
	if (NFTlevelRareTextBlock) {
		NFTlevelRareTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTrare));
	}
}

void UItemBaseWidget::SetNFTactiveStatus(StatusItem NFTstatus)
{
	if (NFTactiveStatusTextBlock) {
		NFTactiveStatusTextBlock->SetText(UEnum::GetDisplayValueAsText(NFTstatus));
	}
}