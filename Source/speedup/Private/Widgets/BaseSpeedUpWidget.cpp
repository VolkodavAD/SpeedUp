// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BaseSpeedUpWidget.h"

/*void UBaseSpeedUpWidget::Hide()
{
	HidePrep();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBaseSpeedUpWidget::Show()
{
	ShowPrep();
	SetVisibility(ESlateVisibility::Visible);
}
*/
void UBaseSpeedUpWidget::CopyMessageToClipboard(FString text)
{
	FPlatformMisc::ClipboardCopy(*text);
}

FString UBaseSpeedUpWidget::PasteMessageFromClipboard()
{
	FString ClipboardContent;
	FPlatformMisc::ClipboardPaste(ClipboardContent);
	return ClipboardContent;
}
