// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GeoPath.generated.h"

struct FDateTime;
/*
 * 
 */
USTRUCT(BlueprintType)
struct FGeoPointInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PointID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointLocationEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PointSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PointDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeStamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime  CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime DeltaTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name = "Path";
};

USTRUCT(BlueprintType)
struct FGeoLocationInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointLocationEnd = FVector2D();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeStamp = 0.0f;
};

UCLASS(Blueprintable)
class SPEEDUP_API UGeotPoint : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGeoPointInfo Pointinfo;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PointID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PointSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime DeltaTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name = "Path";
	*/
	void SetGeoPointInfo(FGeoPointInfo AddedGeoPointInfo);
	FGeoPointInfo GetGeoPointInfo();
};

USTRUCT(BlueprintType)
struct FGeoPathinfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		int PathID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		int ItemID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		int SlotID = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	//TArray<FMovePoint> PointInPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		float PathLength = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		int PathTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float minSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float maxSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float AverageSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float RangeSpeedMin = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float RangeSpeedMax = 0.0f;
};


UCLASS(Blueprintable)
class SPEEDUP_API UGeoPath : public UObject
{
	GENERATED_BODY()

	UGeoPath();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "BaseData")
	FGeoPathinfo UserPathInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	TArray<FGeoPointInfo> PointsInPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrevelPath")
	TArray<FGeoPathinfo> PartsOfPath;

	bool PathIsActiv = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime StartPathTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime StopPathTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrevelPath")
	FGeoLocationInfo LastPointLocation;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UDataTable *DataTable_Puths;
	*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	//TArray<FGeoPathinfo> PlayerPointsInfoInPath;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	//TArray<FGeoPointInfo> PointsInPath;

	UFUNCTION(BlueprintCallable)
	void SetStatusActive(bool NewStatusActive);
	UFUNCTION(BlueprintCallable)
	bool GetStatusActive();
	UFUNCTION(BlueprintCallable)
	void SetPathID(int PathID);
	UFUNCTION(BlueprintCallable)
	void SetSlotID(int SlotID);
	UFUNCTION(BlueprintCallable)
	void SetItemID(int ItemID);

	UFUNCTION(BlueprintCallable)
	void AddPoint(const FGeoPointInfo AddedPoint);

	UFUNCTION(BlueprintCallable)
	void AddPointByLocationVelocity(const int AddedPointID, const FVector2D AddedPointLocation, const float AddedPointSpeed, const FDateTime CurrentTime);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//bool GetPoint(int IndexPoint, UGeotPoint &ResultPoit);

	UFUNCTION(BlueprintCallable)
	bool SavePuthInDataTable(FString RowName, UDataTable* DataTable_Puths);
};