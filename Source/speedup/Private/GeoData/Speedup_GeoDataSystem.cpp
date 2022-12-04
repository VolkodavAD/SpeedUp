// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
#include "..\..\speedupGameModeBase.h"
#include "Engine.h" 	
#include "Kismet/KismetMathLibrary.h"
#include "Misc/DateTime.h"
//#include "Logging/LogMacros.h"
//#include "Service.h"
//#include "/Engine/Plugins/Runtime/LocationServicesBPLibrary/Source/LocationServicesBPLibrary/Classes/LocationServicesImpl.h"
//#include "LocationServicesImpl.h"
//#include "LocationServicesBPLibrary.h"
//#include "LocationServicesBPLibraryModule.h"

USpeedup_GeoDataSystem::USpeedup_GeoDataSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	//UGeoPath* AddedPath01 = NewObject<UGeoPath>();
	//ActivPath.Init(AddedPath01, 3);
	//SetComponentTickEnabled(false);
}

void USpeedup_GeoDataSystem::ReInitServis_Implementation()
{
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

	for (int32 i = 0; i < 3; ++i)
	{
		//ActivPath.Add(NewObject<UGeoPath>());
		ActivPath[i] = NewObject<UGeoPath>();
		ActivPath[i]->SetSlotID(i);
		ActivPath[i]->SetPathID(-1);
		ActivPath[i]->SetItemID(-1);
		ActivPath[i]->SetStatusActive(false);
	}
}

FGeoLocationInfo USpeedup_GeoDataSystem::GetLastLocation_Implementation()
{
	FGeoLocationInfo CurrentPoint;
	CurrentPoint.PointLocation = FVector2D();
	CurrentPoint.TimeStamp = 0.0f;
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

/* -------- semple -------
FTimerDelegate TimerDel;

FTimerHandle TimerHandle;

int32 MyInt = 10;
float MyFloat = 20.f;
FTimerDelegate TimerDelegatePuth01;
//Binding the function with specific values
TimerDel.BindUFunction(this, FName("MyUsefulFunction"), MyInt, MyFloat);
//Calling MyUsefulFunction after 5 seconds without looping
GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 5.f, false);
*/
void USpeedup_GeoDataSystem::RestartTrackPath(int ItemID, int PathID, int SlotID)
{
	ReInitServis();
	if (ServiceEnable && ServiceInit)
	{
		ActivPath[SlotID] = NewObject<UGeoPath>();
		ActivPath[SlotID]->SetSlotID(SlotID);
		ActivPath[SlotID]->SetPathID(PathID);
		ActivPath[SlotID]->SetItemID(ItemID);
		ActivPath[SlotID]->SetStatusActive(true);

		switch (SlotID)
		{
		case 0:
			TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 0);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle01, TimerDelegatePuth01, 2.0f, true, 0.1f);

			break;
		case 1:
			TimerDelegatePuth02.BindUFunction(this, FName("UpdateCurrentPath"), 1);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle02, TimerDelegatePuth02, 2.0f, true, 0.1f);
			break;
		case 2:
			TimerDelegatePuth03.BindUFunction(this, FName("UpdateCurrentPath"), 2);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle03, TimerDelegatePuth03, 2.0f, true, 0.1f);
			break;

		default:
			break;
		}
		ActivPath[SlotID]->PathIsActiv = true;
	}
}

void USpeedup_GeoDataSystem::StartTrackPath(int ItemID, int PathID, int SlotID)
{
	ReInitServis();
	if (ServiceEnable && ServiceInit)
	{
		ActivPath[SlotID] = NewObject<UGeoPath>();
		ActivPath[SlotID]->SetSlotID(SlotID);
		ActivPath[SlotID]->SetPathID(PathID);
		ActivPath[SlotID]->SetItemID(ItemID);
		ActivPath[SlotID]->SetStatusActive(true);

		switch (SlotID)
		{
		case 0:
			TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 0);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle01, TimerDelegatePuth01, DeltaTimePath, true, 0.1f);

			break;
		case 1:
			TimerDelegatePuth02.BindUFunction(this, FName("UpdateCurrentPath"), 1);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle02, TimerDelegatePuth02, DeltaTimePath, true, 0.1f);
			break;
		case 2:
			TimerDelegatePuth03.BindUFunction(this, FName("UpdateCurrentPath"), 2);
			GetWorld()->GetTimerManager().SetTimer(PathTimerHandle03, TimerDelegatePuth03, DeltaTimePath, true, 0.1f);
			break;

		default:
			break;
		}
		ActivPath[SlotID]->PathIsActiv = true;
	}
}


void USpeedup_GeoDataSystem::UpdateCurrentPath(int PathID)
{
	UpdateLocationInPathID(PathID, false);
}

void USpeedup_GeoDataSystem::UpdateCurrentPath01(int PathID)
{
	UpdateLocationInPathID(1, false);
}
void USpeedup_GeoDataSystem::UpdateCurrentPath02(int PathID)
{
	UpdateLocationInPathID(2, false);
}
void USpeedup_GeoDataSystem::StopTrackPath(int ItemID, int PathID, int SlotID)
{
	switch (SlotID)
	{
	case 0:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle01))
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle01);
		}
		break;
	case 1:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle02))
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle02);
		}
		break;
	case 2:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle03))
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle03);
		}
		break;

	default:
		break;
	}

	//UpdateLocationInPathID(SlotID, true);

	ActivPath[SlotID]->SetStatusActive(false);

	//ActivPath[PuthN]->PointsInPath.Empty();
	//SendFinalPath.Broadcast();

	//StartTrackPathEvent(true, ItemID, PathID, SlotID);
}

void USpeedup_GeoDataSystem::UpdateLocationInPathID(int SlotN, bool FinalPath)
{
	FGeoLocationInfo LastLocation = GetLastLocation();
	FGeoPointInfo AddedPoint;
	AddedPoint.PointID = ActivPath[SlotN]->PointsInPath.Num();
	AddedPoint.PointLocation = LastLocation.PointLocation;
	AddedPoint.TimeStamp = LastLocation.TimeStamp;
	AddedPoint.DeltaTime = 0.0f;
	AddedPoint.CurrentTime = FDateTime::UtcNow();

	if (ActivPath[SlotN]->PathIsActiv == true)
	{
		AddedPoint.PointID = ActivPath[SlotN]->PointsInPath.Num();

		if (ActivPath[SlotN]->PointsInPath.Num() > 0)
		{
			//DeltaTimePath = 2.0; //(AddedPoint.CurrentTime - ActivPath[PathID]->PointsInPath.Last().CurrentTime).GetSeconds();
			float DeltaLeghtPath = GetDistanse2Coor(ActivPath[SlotN]->PointsInPath.Last(), AddedPoint);

			AddedPoint.DeltaTime = DeltaTimePath;
			AddedPoint.PointDistance = DeltaLeghtPath;
			AddedPoint.PointSpeed = DeltaLeghtPath / DeltaTimePath;

			ActivPath[SlotN]->UserPathInfo.PathLength += DeltaLeghtPath;
			ActivPath[SlotN]->UserPathInfo.PathTime += DeltaTimePath;
		}
		else
		{
			AddedPoint.DeltaTime = 0.0f;
			AddedPoint.PointDistance = 0.0f;
			AddedPoint.PointSpeed = -1.0f;

			ActivPath[SlotN]->UserPathInfo.PathLength = 0.0f;
			ActivPath[SlotN]->UserPathInfo.PathTime = 0.0f;
		}

		if (UKismetMathLibrary::Abs(AddedPoint.PointLocation.X) > 0.001 && UKismetMathLibrary::Abs(AddedPoint.PointLocation.X) > 0.001)
		{
			ActivPath[SlotN]->AddPoint(AddedPoint);
			AddedPoint.PointDistance = 0.0f;
			AddedPoint.PointSpeed = 0.0f;
		}
	}

	if ((ActivPath[SlotN]->UserPathInfo.PathTime > 120) || (FinalPath))
	{
		float PathSumSpeed = 0.0f;
		float PathMinSpeed = 0.0f;
		float PathMaxSpeed = 0.0f;
		float PathAverageSpeed = 0.0f;
		float PathDistance = 0.0f;

		for (int32 i = 0; i < ActivPath[SlotN]->PointsInPath.Num(); ++i)
		{
			if (i == 0)
			{
				PathMinSpeed = ActivPath[SlotN]->PointsInPath[i].PointSpeed;
				PathMaxSpeed = ActivPath[SlotN]->PointsInPath[i].PointSpeed;
			}
			else
			{
				PathMinSpeed = PathMinSpeed > ActivPath[SlotN]->PointsInPath[i].PointSpeed ? ActivPath[SlotN]->PointsInPath[i].PointSpeed : PathMinSpeed;
				PathMaxSpeed = PathMaxSpeed < ActivPath[SlotN]->PointsInPath[i].PointSpeed ? ActivPath[SlotN]->PointsInPath[i].PointSpeed : PathMaxSpeed;
			}
			PathSumSpeed += ActivPath[SlotN]->PointsInPath[i].PointSpeed;
		}
		PathAverageSpeed = PathSumSpeed / ActivPath[SlotN]->PointsInPath.Num();

		FGeoPathinfo AddedPathPart;

		AddedPathPart.PathID = ActivPath[SlotN]->UserPathInfo.PathID;
		AddedPathPart.AverageSpeed = ActivPath[SlotN]->UserPathInfo.AverageSpeed;
		AddedPathPart.PathLength = ActivPath[SlotN]->UserPathInfo.PathLength;
		AddedPathPart.PathTime = ActivPath[SlotN]->UserPathInfo.PathTime;
		AddedPathPart.maxSpeed = ActivPath[SlotN]->UserPathInfo.maxSpeed;
		AddedPathPart.minSpeed = ActivPath[SlotN]->UserPathInfo.minSpeed;

		ActivPath[SlotN]->PartsOfPath.Add(AddedPathPart);
		ActivPath[SlotN]->UserPathInfo.AverageSpeed = PathSumSpeed / ActivPath[SlotN]->PointsInPath.Num();

		if (FinalPath)
		{
			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->FinalPathItem(ActivPath[SlotN]->UserPathInfo.ItemID, ActivPath[SlotN]->UserPathInfo.PathID, SlotN, PathDistance, PathAverageSpeed);
		}
		else
		{

			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->UpdatePathItem(ActivPath[SlotN]->UserPathInfo.ItemID, ActivPath[SlotN]->UserPathInfo.PathID, PathDistance, PathAverageSpeed);
		}

		ActivPath[SlotN]->PointsInPath.Empty();
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
}
float USpeedup_GeoDataSystem::GetLeghtPath_Today()
{
	return LeghtPath_Today;
}
float USpeedup_GeoDataSystem::GetLeghtPath_Weekly()
{
	return LeghtPath_Weekly;
}
float USpeedup_GeoDataSystem::GetLeghtPath_Total()
{
	return LeghtPath_Total;
}

//void USpeedup_GeoDataSystem::UpdateDistance(int DeactivePathID, int DeactivNFDId, int avg_velocity, int avg_distance)
//{
//}
void USpeedup_GeoDataSystem::UpdateDistance_Implementation(int DeactivePathID, int DeactivNFDId, float avg_velocity, float avg_distance)
{
}