// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
#include "Misc/DateTime.h"
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
	UGeoPath* AddedPath01 = NewObject<UGeoPath>();
	ActivPath.Init(AddedPath01, 3);

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

FGeoPointInfo USpeedup_GeoDataSystem::GetLastLocation_Implementation()
{
	FGeoPointInfo CurrentPoint;
	CurrentPoint.Name = "0";
	CurrentPoint.CurrentTime = 0.0f;
	CurrentPoint.PointLocation = FVector2D();
	CurrentPoint.PointVelosity = 0.0f;
	return CurrentPoint;
}
float USpeedup_GeoDataSystem::GetDistanse2Coor_Implementation(FGeoPointInfo PointStart, FGeoPointInfo PointEnd)
{
	return 0.0f;
}

bool USpeedup_GeoDataSystem::HaveActivePath()
{
	for (int32 i = 0; i < ActivPath.Num(); ++i)
	{
		if (ActivPath[i]->PathIsActiv == true) return true;
	}
	return false;
}

void USpeedup_GeoDataSystem::StartActivPath01(int PuthN)
{
}
void USpeedup_GeoDataSystem::StopActivPath01(int PuthN)
{
}

void USpeedup_GeoDataSystem::StartPath(int PuthN)
{
	if (!ServiceEnable)
	{
		return;
	}
	if (PathTimerHandle.IsValid() && !GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle, this, &USpeedup_GeoDataSystem::UpdateLocation, 6.0f, true, 2.0f);
	}
	ActivPath[PuthN]->PathIsActiv = true;
}


void USpeedup_GeoDataSystem::StopPath(int PuthN)
{
	if (PathTimerHandle.IsValid())
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle) && !HaveActivePath())
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle);
		}
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
    }*/
}

void USpeedup_GeoDataSystem::UpdateLocationSneckers()
{
	FGeoPointInfo AddedPoint = GetLastLocation();

	for (int32 i = 0; i < ActivPath.Num(); ++i)
	{
		if (ActivPath[i]->PathIsActiv == true)
		{
			FGeoPointInfo AddedPoint_i = AddedPoint;
			AddedPoint_i.PointID = ActivPath[i]->PlayerPathInfo.PointsInPath.Num();
			if (ActivPath[i]->PlayerPathInfo.PointsInPath.Num() > 0)
			{
				float DeltaTimePath = (AddedPoint.CurrentTime - ActivPath[i]->PlayerPathInfo.PointsInPath.Last().CurrentTime).GetSeconds();
				float DeltaLeghtPath = GetDistanse2Coor(ActivPath[i]->PlayerPathInfo.PointsInPath.Last(), AddedPoint);
				AddedPoint.PointVelosity = DeltaLeghtPath / DeltaTimePath;
			}
			else
			{
				AddedPoint.PointVelosity = -1.0;
			}
			ActivPath[i]->AddPoint(AddedPoint);
		}
	}

	/*
	AddedPoint.PointID = LastSneakersPathID++;
	if (ActivSneakersPath->PlayerPathInfo.PointsInPath.Num() != 0)
	{
		float DeltaTimePath = (AddedPoint.CurrentTime - ActivSneakersPath->PlayerPathInfo.PointsInPath.Last().CurrentTime).GetSeconds();
		float DeltaLeghtPath = GetDistanse2Coor(ActivSneakersPath->PlayerPathInfo.PointsInPath.Last(), AddedPoint);
		AddedPoint.PointVelosity = DeltaLeghtPath / DeltaTimePath;
	}
	else
	{
		AddedPoint.PointVelosity = -1.0;
	}
	ActivSneakersPath->AddPoint(AddedPoint);
	*/
}

bool USpeedup_GeoDataSystem::InitService()
{
	return false;
}
bool USpeedup_GeoDataSystem::StartService()
{
	return false;
}

//FTimerDelegate TimerDel;
//FTimerHandle TimerHandle;

//int32 MyInt = 10;
//float MyFloat = 20.f;

//Binding the function with specific values
//TimerDel.BindUFunction(this, FName("MyUsefulFunction"), MyInt, MyFloat);
//Calling MyUsefulFunction after 5 seconds without looping
//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 5.f, false);