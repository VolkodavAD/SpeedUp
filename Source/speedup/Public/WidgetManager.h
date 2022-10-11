// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widgets/BaseSpeedUpWidget.h"
#include "WidgetManager.generated.h"

class USpeedUpGameInstance;

USTRUCT()
struct FWidgetInfo {
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
        TSubclassOf<UBaseSpeedUpWidget> widgetClass;

    UPROPERTY()
        UBaseSpeedUpWidget* widget;

    UPROPERTY()
        int zOrder;
};

UCLASS()
class SPEEDUP_API UWidgetManager : public UObject
{
	GENERATED_BODY()
        UPROPERTY()
        TMap<FString, FWidgetInfo> widgets;

public:

    UFUNCTION(BlueprintCallable)
        bool AddWidget(FString name,
            TSubclassOf<UBaseSpeedUpWidget> widgetClass,
            int zOrder = 0);


    //UFUNCTION(BlueprintCallable)
    //    void InitAndStartCaching(USpeedUpGameInstance* gi);

    //UFUNCTION(BlueprintCallable)
    //    void EndCaching();

    UFUNCTION(BlueprintCallable)
        bool ShowWidget(FString name);

    UFUNCTION(BlueprintCallable)
        bool HideWidget(FString name);

    UFUNCTION(BlueprintCallable)
        UBaseSpeedUpWidget* GetWidget(FString name);

    UFUNCTION(BlueprintCallable)
        UBaseSpeedUpWidget* CreateTransientWidget(TSubclassOf<UBaseSpeedUpWidget> widgetClass, UWorld* world, FString name);
    
};
