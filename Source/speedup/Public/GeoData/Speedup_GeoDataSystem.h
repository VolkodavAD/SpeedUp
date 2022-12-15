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
//class UHTTPAPIComponent;

	//UHTTPAPIComponent* HTTPAPI;
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateBindableEvent, int, Path);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinalBindableEvent, int, Path);

DECLARE_DELEGATE_OneParam(FDataIsReadyDelegate, float);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateName_TestDel02, float)

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


	FTimerDelegate TimerDelegatePuth01;
	FTimerDelegate TimerDelegatePuth02;
	FTimerDelegate TimerDelegatePuth03;

	FTimerHandle PathTimerHandle01;
	FTimerHandle PathTimerHandle02;
	FTimerHandle PathTimerHandle03;

	UPROPERTY(BlueprintAssignable)
	FUpdateBindableEvent SendPartPath;
	UPROPERTY(BlueprintAssignable)
	FFinalBindableEvent SendFinalPath;

	float DeltaTimePath = 5.0;

	// отправка данных на сервер
	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateCurrentPath(int PathID);
	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateCurrentPath01(int PathID);
	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateCurrentPath02(int PathID);
	UFUNCTION(BlueprintCallable, Category = "GeoData")
	void UpdateLocationInPathID(int PathID, bool FinalPath = false);
	
	// работа с Модулем девайса
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void ReInitServis();
	void ReInitServis_Implementation();
	// работа с Модулем девайса

	UFUNCTION(BlueprintImplementableEvent, Category = "GeoData")
	void UpdateLocation();
	void UpdateLocation_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	FGeoLocationInfo GetLastLocation();
	FGeoLocationInfo GetLastLocation_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	float GetDistanse2Coor(FVector2D PointStart, FVector2D PointEnd);
	float GetDistanse2Coor_Implementation(FVector2D PointStart, FVector2D PointEnd);

	UFUNCTION(BlueprintCallable)
	void RestartTrackPath(int ItemID, int PathID, int SlotID);
	UFUNCTION(BlueprintCallable)
	void StartTrackPath(int ItemID, int PathID, int SlotID);
	UFUNCTION(BlueprintCallable)
	void StopTrackPath(int ItemID, int PathID, int SlotID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	void UpdateDistance(int DeactivePathID, int DeactivNFDId, float avg_velocity, float avg_distance);
	void UpdateDistance_Implementation(int DeactivePathID, int DeactivNFDId, float avg_velocity, float avg_distance);

public:

	float LeghtPath_Today;
	float LeghtPath_Weekly;
	float LeghtPath_Total;


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
