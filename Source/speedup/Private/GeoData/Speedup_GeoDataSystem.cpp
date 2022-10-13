// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
#include "LocationServicesImpl.h"
//#include "LocationServicesBPLibrary.h"

// Sets default values for this component's properties
USpeedup_GeoDataSystem::USpeedup_GeoDataSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	ActivSneakersPath = NewObject<UGeoPath>();
	ActivCarPath = NewObject<UGeoPath>();
	ActivPlanePath = NewObject<UGeoPath>();

	SpeedUp_ULocationServices = NewObject<ULocationServices>();

	if (InitServis())
	{
		ServisInit = true;
		if (StartServis())
		{ 
			ServisStart = true;
		}
		else
		{
			ServisStart = false;
		}
	}
	else
	{
		ServisInit = false;
	}

	//https://docs.unrealengine.com/4.26/en-US/PythonAPI/class/LocationServices.html
	// https://docs.unrealengine.com/5.0/en-US/PythonAPI/class/LocationServicesData.html#unreal.LocationServicesData
	//unreal.LocationServices
}


// Called when the game starts
void USpeedup_GeoDataSystem::BeginPlay()
{
	Super::BeginPlay();
	//if (Sneakers_TimerHandle.IsValid())
	//GetWorld()->GetTimerManager().SetTimer(Sneakers_TimerHandle, this, &USpeedup_GeoDataSystem::RepeatingFunction, 1.0f, true, 2.0f);
	// ...	
}

FGeoPointInfo USpeedup_GeoDataSystem::GetLastLocstion()
{
	FLocationServicesData LastFLocationServicesData;
	if (SpeedUp_ULocationServices != nullptr)
	{
		LastFLocationServicesData = SpeedUp_ULocationServices->GetLastKnownLocation();
	}
	FGeoPointInfo CurrentPoint;
	CurrentPoint.PointLocation = FVector2D(LastFLocationServicesData.Longitude, LastFLocationServicesData.Latitude);
	return CurrentPoint;
}

void USpeedup_GeoDataSystem::StartPath(FTimerHandle CurrentTimerH)
{
	if (!ServisEnable)
	{
		return;
	}
	//GetWorld()->GetTimerManager().SetTimer(CurrentTimerH, this, &USpeedup_GeoDataSystem::RepeatingFunction, 1.0f, true, 2.0f);
	if (ActivSneakersPath != nullptr)
	{
		ActivSneakersPath = NewObject<UGeoPath>();
		if (Sneakers_TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(CurrentTimerH, this, &USpeedup_GeoDataSystem::RepeatingFunction, 1.0f, true, 2.0f);
		}
	}
}

void USpeedup_GeoDataSystem::StopPath(FTimerHandle CurrentTimerH)
{
	//GetWorld()->GetTimerManager().ClearTimer(CurrentTimerH);
}

// Called every frame
void USpeedup_GeoDataSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpeedup_GeoDataSystem::RepeatingFunction()
{
   // Once we've called this function enough times, clear the Timer.
   /*if (--RepeatingCallsRemaining <= 0)
   {
		//GetWorld()->GetTimerManager().ClearTimer(Sneakers_TimerHandle);
        // MemberTimerHandle can now be reused for any other Timer.
    }
	*/
    // Do something here...
}


bool USpeedup_GeoDataSystem::InitServis()
{
	//SpeedUp_ULocationServices::InitLocationServices(ELocationAccuracy::LA_Best, 1000.0, 10.0);
	//GeoLocationServis->InitLocationServices(ELocationAccuracy::LA_Best, 1000.0, 10.0);
	if (SpeedUp_ULocationServices != nullptr)
	{
		return SpeedUp_ULocationServices->InitLocationServices(ELocationAccuracy::LA_Best, 1000.0, 10.0);
	}
	return false;
}

bool USpeedup_GeoDataSystem::StartServis()
{
	if (SpeedUp_ULocationServices != nullptr)
	{
		return SpeedUp_ULocationServices->StartLocationServices();
	}
	return false;
}
