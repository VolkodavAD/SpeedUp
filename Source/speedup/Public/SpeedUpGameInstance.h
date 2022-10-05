// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/Object.h"
#include "WidgetManager.h"
#include "SpeedUpGameInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMainMenuPage : uint8
{
    NO_PAGE = 0 UMETA(DisplayName = "No page"),
    WALLET = 1 UMETA(DisplayName = "Wallet"),
    STATISTICS = 2 UMETA(DisplayName = "Statistics"),
    ACTIVE = 3 UMETA(DisplayName = "ActiveNFTs"),
    ITEMS = 4 UMETA(DisplayName = "Items"),
    SHOP = 5 UMETA(DisplayName = "Shop"),
    GENERAL = 6 UMETA(DisplayName = "General")
};


UCLASS()
class SPEEDUP_API USpeedUpGameInstance : public UGameInstance
{
    GENERATED_BODY()
        virtual void Init();

public:
    UPROPERTY(BlueprintReadWrite)
       UWidgetManager* widgetManager;

    UFUNCTION(BlueprintImplementableEvent)
        void InitWidgetManager();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void OpenLevel(const FString& Level, const FString& Options);

    //future function for popup for example copy private code from wallet
    /*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void ShowNewMessagePopup(const FRemoteMessageInfo& message);*/
};
