// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "GeoPath.h"
//#include "GeoReferencingSystem.h"
//#include <Engine.h>
//#include <EngineService.h>
//#include <LocationServicesImpl.h>
//#include "GeoReferencingSystem.h"
//#include "AzureSpatialAnchorsTypes.h"
#include "Speedup_GeoDataSystem.generated.h"

//class ULocationServicesImpl; 
//class ULocationServices;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPEEDUP_API USpeedup_GeoDataSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpeedup_GeoDataSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyBindableEvent);

	FTimerDelegate TimerDelegatePuth01;
	FTimerDelegate TimerDelegatePuth02;
	FTimerDelegate TimerDelegatePuth03;

	FTimerHandle PathTimerHandle01;
	FTimerHandle PathTimerHandle02;
	FTimerHandle PathTimerHandle03;

	UPROPERTY(BlueprintAssignable)
	FMyBindableEvent SendPartPath;

	//UPROPERTY(BlueprintAssignable)
	//FMyBindableEvent SendFinalPath;

	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateCurrentPath(int PuthN);

	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateLocationInPathID(int PathID, bool FinalPath = false);

	UFUNCTION(BlueprintImplementableEvent, Category = "GeoData")
	void UpdateLocation();
	void UpdateLocation_Implementation();

	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateLocationInPath();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void ReInitServis();
	void ReInitServis_Implementation(); 

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	FGeoLocationInfo GetLastLocation();
	FGeoLocationInfo GetLastLocation_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	float GetDistanse2Coor(FGeoPointInfo PointStart, FGeoPointInfo PointEnd);
	float GetDistanse2Coor_Implementation(FGeoPointInfo PointStart, FGeoPointInfo PointEnd);

	UFUNCTION(BlueprintCallable)
	void StartTrackPath(int PuthN);
	UFUNCTION(BlueprintCallable)
	void StopTrackPath(int PuthN);

public:


	float LeghtPath_Today;
	float LeghtPath_Weekly;
	float LeghtPath_Total;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	//class ULocationServices *SpeedupULocationServices;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	//ULocationServicesImpl* SpeedupULocationServicesImpl;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	//class ULocationServicesImpl* SpeedUp_ULocationServices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServiceEnable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServiceInit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServiceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle PathTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle Sneakers_TimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle Car_TimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle Plane_TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	TArray<UGeoPath*> ActivPath;

	UFUNCTION(BlueprintCallable)
	bool HaveActivePath();

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UGeoPath* ActivPath02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UGeoPath* ActivPath03;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	int LastSneakersPathID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	int LastCarPathID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	int LastPlanePathID;

private:
	UFUNCTION(BlueprintCallable)
	void SetServiceEnable(bool value);
	UFUNCTION(BlueprintCallable)
	void SetServiceStart(bool value);
	UFUNCTION(BlueprintCallable)
	void SetServiceInit(bool value);

	UFUNCTION(BlueprintCallable)
	float GetLeghtPath_Today();
	UFUNCTION(BlueprintCallable)
	float GetLeghtPath_Weekly();
	UFUNCTION(BlueprintCallable)
	float GetLeghtPath_Total();
};
