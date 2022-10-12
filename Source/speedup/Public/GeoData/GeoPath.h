// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GeoPath.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FGeoPointInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointVelosity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name = "Path";
};

UCLASS(Blueprintable)
class SPEEDUP_API UGeotPoint : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D PointVelosity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name = "Path";

	void SetGeoPointInfo(FGeoPointInfo AddedGeoPointInfo);
};

USTRUCT(BlueprintType)
struct FGeoPathinfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	//TArray<FMovePoint> PointInPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		float PathLangth = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		int TotalTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float minVelosity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float maxVelosity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
		TArray<FGeoPointInfo> PointsInPath;
};

UCLASS(Blueprintable)
class SPEEDUP_API UGeoPath : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	FGeoPathinfo PlayerPathInfo;
	
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UDataTable *DataTable_Puths;
	*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	//TArray<FGeoPathinfo> PlayerPointsInfoInPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	TArray<UGeotPoint*> PointsInPath;

	void AddPoint(const FGeoPointInfo AddedPoint);

	UFUNCTION(BlueprintCallable)
	void AddPointByLocationVelocity(const FVector2D AddedPointLocation, const FVector2D AddedPointVelosity, const int CurrentTime);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetPoint(int IndexPoint, UGeotPoint &ResultPoit);

	UFUNCTION(BlueprintCallable)
	bool SavePuthInDataTable(FString RowName, UDataTable* DataTable_Puths);
};