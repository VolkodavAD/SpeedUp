// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/Object.h"
#include "WidgetManager.h"
#include "Engine/DataTable.h"
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

/*"data": {
    "id": 2,
     "email" : "hahalol915@gmail.com",
     "email_confirmed" : true,
     "balances" : 
     {
     "dks_wallet": "0x728c2259f6a07c13ec181bcbafd9c28ede9585c896beb25dd5b4dda6ba422f7a",
     "dks_balance" : 0,
     "internal_balance" : 0
    },
        "energy" : 
        {
        "user_id": 2,
        "capacity" : 3,
        "spend_part" : 4,
        "updated_at" : "2022-10-14T19:47:43.4619+03:00",
         "active" : true
        }
}*/

USTRUCT(BlueprintType)
struct Fbalances : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString dks_wallet;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float dks_balance;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float internal_balance;
};

USTRUCT(BlueprintType)
struct Fenergy : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int user_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        uint8 capacity; // Byte
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        uint8 spend_part;  // Byte
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString updated_at;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool active;
};

USTRUCT(BlueprintType)
struct FUserInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int id = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString email;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool email_confirmed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        Fbalances  Balance;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        Fenergy Energy;
};

UCLASS()
class SPEEDUP_API USpeedUpGameInstance : public UGameInstance
{
    GENERATED_BODY()
        virtual void Init();

public:
    UPROPERTY(BlueprintReadWrite)
       UWidgetManager* widgetManager;

    //UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseData")
        //bool email_confirmed;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "User")
        FUserInfo UserInfo;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
        bool IsActivItem;

    UFUNCTION(BlueprintImplementableEvent)
        void InitWidgetManager();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void OpenLevel(const FString& Level, const FString& Options);

    //future function for popup for example copy private code from wallet
    /*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void ShowNewMessagePopup(const FRemoteMessageInfo& message);*/
};

