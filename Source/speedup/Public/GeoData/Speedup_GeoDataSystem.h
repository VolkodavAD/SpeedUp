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
	
	UPROPERTY(BlueprintAssignable)
	FMyBindableEvent OnAwesomeness;
	// Create Event
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void OnDeath();
	void OnDeath_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GeoData")
	void UpdateLocation();
	void UpdateLocation_Implementation();
	UFUNCTION(BlueprintCallable)
	bool InitService();
	UFUNCTION(BlueprintCallable)
	bool StartService();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	FGeoPointInfo GetLastLocation();

	UFUNCTION(BlueprintCallable)
	void StartPath(FTimerHandle CurrentTimerH);
	UFUNCTION(BlueprintCallable)
	void StopPath(FTimerHandle CurrentTimerH);

	UFUNCTION(BlueprintCallable)
	void StartPathInSneckers();
	UFUNCTION(BlueprintCallable)
	void StopPathInSneckers();

public:
	
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
	FTimerHandle Sneakers_TimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle Car_TimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	FTimerHandle Plane_TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UGeoPath* ActivSneakersPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UGeoPath* ActivCarPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseData")
	UGeoPath* ActivPlanePath;


private:
	UFUNCTION(BlueprintCallable)
		void SetServiceEnable(bool value);
	UFUNCTION(BlueprintCallable)
		void SetServiceStart(bool value);
	UFUNCTION(BlueprintCallable)
		void SetServiceInit(bool value);
};
