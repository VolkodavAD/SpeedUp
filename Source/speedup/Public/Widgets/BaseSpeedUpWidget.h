// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSpeedUpWidget.generated.h"

/**
 * 
 */

class USpeedUpGameInstance;

UCLASS()
class SPEEDUP_API UBaseSpeedUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
		USpeedUpGameInstance* gi;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool needsCaching = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool hideAfterCache = true;

    UFUNCTION(BlueprintImplementableEvent)
        void StartCache();

    UFUNCTION(BlueprintImplementableEvent)
        void EndCache();

    UFUNCTION(BlueprintImplementableEvent)
        void ShowPrep();

    UFUNCTION(BlueprintImplementableEvent)
        void HidePrep();

    UFUNCTION(BlueprintCallable)
        void Hide();
    UFUNCTION(BlueprintCallable)
        void Show();
};
