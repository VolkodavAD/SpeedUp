// Fill out your copyright notice in the Description page of Project Settings.


#include "widgets/BaseWalletWidget.h"


//void UBaseWalletWidget::NativeOnInitialized()
//{
	//RefreshSPDBalance();
//}

//void UBaseWalletWidget::RefreshSPDBalance()
//{
	//if (SPDBalance) {
		//SPDBalance->SetText(FText::FromString("0,01"));
	//}
//}


void UBaseWalletWidget::SetWalletInfo(FWalletTransaction NewWalletInfo)
{
	WalletInfo = NewWalletInfo;
}

FWalletTransaction UBaseWalletWidget::GetWalletHistoryInfo()
{
	return WalletInfo;
}

//void UItemManager::AddItem(UItem* AddedItem)
//{
	//MyItems.Add(AddedItem);
//}


void UBaseWalletWidget::AddTransaction(FWalletTransaction AddedTransaction)
{

	MyHistory.Add(AddedTransaction);
}