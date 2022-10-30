// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ItemType : uint8
{
	Unnone		UMETA(DisplayName = "Unnone"),
	Sneakers	UMETA(DisplayName = "Sneakers"),
	Car			UMETA(DisplayName = "Car"),
	airplane	UMETA(DisplayName = "airplane"),
};

UENUM(BlueprintType)
enum class ItemLevelRarity : uint8
{
	Common		UMETA(DisplayName = "Common"),
	Rare		UMETA(DisplayName = "Rare"),
	Legendary	UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class StatusItem : uint8
{
	Deactive	UMETA(DisplayName = "Deactive"),
	Active		UMETA(DisplayName = "Active"),
};

// Base constant information about item. For DataTable
USTRUCT(BlueprintType)
struct FBaseItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int ItemID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		FString ItemName = "Item";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		ItemType Type = ItemType::Sneakers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		ItemLevelRarity ItemRarity = ItemLevelRarity::Common;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int ItemLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		StatusItem ItemStatus = StatusItem::Deactive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		FString ItemImage = "image_url";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int CollectionID = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int	Chain_ID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		bool Minted = false;
};

UCLASS(Blueprintable)
class SPEEDUP_API UItem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	FBaseItemInfo ItemInfo;

	int TimeEnergyRestore = 0;

	UItem();

public:
	// For test is 3 variable is public.
	UPROPERTY(EditDefaultsOnly, Category = "ItemState")
	int MaxEnergy = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	int Energy = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	int CurrentTimeToEnergyRestore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	UTexture2D* ItemImage;
	// image for review
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	//UTexture2D* ItemIcon;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
	//StatusItem Status = StatusItem::Deactive;

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(FBaseItemInfo NewItemInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FBaseItemInfo GetItemInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetItemID();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ItemType GetType();

	UFUNCTION(BlueprintCallable)
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	void SetItemStatus(StatusItem NewItemStatus);
};
