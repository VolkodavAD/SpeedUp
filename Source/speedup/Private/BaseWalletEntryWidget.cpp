// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWalletEntryWidget.h"

void UBaseWalletEntryWidget::NativeOnInitialized()
{
	HistoryDateUpdate();
	StepsWalkingCountUpdate();
	KmDayWalkingCountUpdate();
	SPDDayEarnedUpdate();
}

void UBaseWalletEntryWidget::HistoryDateUpdate()
{
	if (TextBlockDate) {
		TextBlockDate->SetText(FText::FromString("Aug 25"));
	}
}
void UBaseWalletEntryWidget::StepsWalkingCountUpdate()
{
	if (TextBlockStepsWalked) {
		TextBlockStepsWalked->SetText(FText::FromString("3012 steps walked"));
	}
}
void UBaseWalletEntryWidget::KmDayWalkingCountUpdate()
{
	if (TextBlockKmWalked) {
		TextBlockKmWalked->SetText(FText::FromString("1,25 km walked"));
	}
}

void UBaseWalletEntryWidget::SPDDayEarnedUpdate()
{
	if (TextBlockSPDEarned) {
		TextBlockSPDEarned->SetText(FText::FromString("+1,15 SPD"));
	}
}