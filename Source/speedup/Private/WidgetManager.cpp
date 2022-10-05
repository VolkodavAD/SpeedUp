// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetManager.h"

bool UWidgetManager::AddWidget(FString name, TSubclassOf<UBaseSpeedUpWidget> widgetClass, int zOrder)
{
    return false;
}

bool UWidgetManager::ShowWidget(FString name)
{
    return false;
}

bool UWidgetManager::HideWidget(FString name)
{
    return false;
}

UBaseSpeedUpWidget* UWidgetManager::GetWidget(FString name)
{
    return nullptr;
}

UBaseSpeedUpWidget* UWidgetManager::CreateTransientWidget(TSubclassOf<UBaseSpeedUpWidget> widgetClass, UWorld* world, FString name)
{
    return nullptr;
}
