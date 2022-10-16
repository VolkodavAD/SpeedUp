// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
//#include "Service.h"
//#include "/Engine/Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary/Classes/LocationServicesImpl.h"
//#include "LocationServicesImpl.h"
//#include "LocationServicesBPLibrary.h"
//#include "LocationServicesBPLibraryModule.h"

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


	if (InitService())
	{
		ServiceInit = true;
		if (StartService())
		{ 
			ServiceStart = true;
		}
		else
		{
			ServiceStart = false;
		}
	}
	else
	{
		ServiceInit = false;
	}

	//https://docs.unrealengine.com/4.26/en-US/PythonAPI/class/LocationServices.html
	// https://docs.unrealengine.com/5.0/en-US/PythonAPI/class/LocationServicesData.html#unreal.LocationServicesData
	// https://www.protechtraining.com/blog/post/tutorial-android-location-service-example-198
	// https://forums.unrealengine.com/t/mobile-enabling-location-sevices/385104/10
	//unreal.LocationServices
}


void USpeedup_GeoDataSystem::SetServiceEnable(bool value)
{
	ServiceEnable = value;
}
void USpeedup_GeoDataSystem::SetServiceStart(bool value)
{
	ServiceStart = value;
}

void USpeedup_GeoDataSystem::SetServiceInit(bool value)
{
	ServiceInit = value;
}

// Called when the game starts
void USpeedup_GeoDataSystem::BeginPlay()
{
	Super::BeginPlay();
	//if (Sneakers_TimerHandle.IsValid())
	//GetWorld()->GetTimerManager().SetTimer(Sneakers_TimerHandle, this, &USpeedup_GeoDataSystem::UpdateLocation, 1.0f, true, 2.0f);
	// ...	
}

/*
FGeoPointInfo USpeedup_GeoDataSystem::GetLastLocation()
{
	FGeoPointInfo CurrentPoint;
	return CurrentPoint;
}*/


FGeoPointInfo USpeedup_GeoDataSystem::GetLastLocation_Implementation()
{
	//FLocationServicesData LastFLocationServicesData;
	//if ((SpeedupULocationServices != nullptr) && ServiceInit && ServiceStart)
	//{
		//LastFLocationServicesData = SpeedupULocationServices->GetLastKnownLocation();
	//}
	FGeoPointInfo CurrentPoint;
	//CurrentPoint.PointLocation = FVector2D(LastFLocationServicesData.Longitude, LastFLocationServicesData.Latitude);
	return CurrentPoint;
}

void USpeedup_GeoDataSystem::StartPath(FTimerHandle CurrentTimerH)
{
	if (!ServiceEnable)
	{
		return;
	}
	//GetWorld()->GetTimerManager().SetTimer(CurrentTimerH, this, &USpeedup_GeoDataSystem::UpdateLocation, 1.0f, true, 2.0f);
	if (ActivSneakersPath != nullptr)
	{
		ActivSneakersPath = NewObject<UGeoPath>();
		if (Sneakers_TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(CurrentTimerH, this, &USpeedup_GeoDataSystem::UpdateLocation, 6.0f, true, 2.0f);
		}
	}
}

void USpeedup_GeoDataSystem::OnDeath_Implementation() {};

void USpeedup_GeoDataSystem::StartPathInSneckers()
{
	StartPath(Sneakers_TimerHandle);
}

void USpeedup_GeoDataSystem::StopPathInSneckers()
{
	StopPath(Sneakers_TimerHandle);
}

void USpeedup_GeoDataSystem::StopPath(FTimerHandle CurrentTimerH)
{
	if (CurrentTimerH.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CurrentTimerH);
	}
}

// Called every frame
void USpeedup_GeoDataSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpeedup_GeoDataSystem::UpdateLocation_Implementation()
{
	GetLastLocation();
   // Once we've called this function enough times, clear the Timer.
   /*if (--RepeatingCallsRemaining <= 0)
   {
		//GetWorld()->GetTimerManager().ClearTimer(Sneakers_TimerHandle);
        // MemberTimerHandle can now be reused for any other Timer.
    }
	*/
    // Do something here...
}


bool USpeedup_GeoDataSystem::InitService()
{
	return false;
}

bool USpeedup_GeoDataSystem::StartService()
{
	return false;
}
