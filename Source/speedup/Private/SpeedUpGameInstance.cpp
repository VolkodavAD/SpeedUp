// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUpGameInstance.h"

void USpeedUpGameInstance::Init()
{
	widgetManager = NewObject<UWidgetManager>();
	InitWidgetManager();
}
