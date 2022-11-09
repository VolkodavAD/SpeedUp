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


void UBaseWalletWidget::SetWalletInfo(UWalletTransaction* NewWalletInfo)
{
	WalletInfo = NewWalletInfo;
}

UWalletTransaction* UBaseWalletWidget::GetWalletHistoryInfo()
{
	return WalletInfo;
}

//void UItemManager::AddItem(UItem* AddedItem)
//{
	//MyItems.Add(AddedItem);
//}


void UBaseWalletWidget::AddTransaction(UWalletTransaction* AddedTransaction)
{

	MyHistory.Add(AddedTransaction);
}

UWalletTransaction::UWalletTransaction()
{

}
