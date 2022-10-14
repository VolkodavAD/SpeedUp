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

class ULocationServicesImpl; 
class ULocationServices;

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

	void RepeatingFunction();

	UFUNCTION(BlueprintCallable)
	bool InitServis();
	UFUNCTION(BlueprintCallable)
	bool StartServis();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GeoData")
	FGeoPointInfo GetLastLocation();

	UFUNCTION(BlueprintCallable)
	void StartPath(FTimerHandle CurrentTimerH);
	UFUNCTION(BlueprintCallable)
	void StopPath(FTimerHandle CurrentTimerH);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	ULocationServices* SpeedupULocationServices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	ULocationServicesImpl* SpeedupULocationServicesImpl;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoData")
	//class ULocationServicesImpl* SpeedUp_ULocationServices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServisEnable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServisInit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseData")
	bool ServisStart;

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
};
