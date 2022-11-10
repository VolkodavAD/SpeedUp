// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
#include "..\..\speedupGameModeBase.h"
#include "Engine.h"
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
		//ActivPath[i] = NewObject<UGeoPath>();
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

void USpeedup_GeoDataSystem::StartTrackPath(int ItemID, int PathID, int SlotID)
{
	ReInitServis();
/*
	UE_LOG(LogTemp, Warning, TEXT("ServiceEnable : %d"), ServiceEnable);

	if (PathTimerHandle.IsValid())
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("PathTimerHandle.IsValid - true")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("PathTimerHandle.IsValid - false")));

	if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle))
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("IsTimerActive - true")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("IsTimerActive - false")));
*/
	/*
	if (ActivPath[SlotID] == nullptr)
	{
		ActivPath[SlotID] = NewObject<UGeoPath>();
	}
	*/
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
		TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 1);
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle02, TimerDelegatePuth02, 2.0f, true, 0.1f);
		break;
	case 2:
		TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 2);
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle03, TimerDelegatePuth03, 2.0f, true, 0.1f);
		break;

	default:
		break;
	}

	//GetWorld()->GetTimerManager().SetTimer(PathTimerHandle, this, &USpeedup_GeoDataSystem::UpdateLocationInPath, 6.0f, true, 2.0f);
	ActivPath[SlotID]->PathIsActiv = true;

	StartTrackPathEvent(false, ItemID, PathID, SlotID);
}

void USpeedup_GeoDataSystem::StartTrackPathEvent_Implementation(bool Stop,int ItemID, int PathID, int SlotID)
{}

void USpeedup_GeoDataSystem::UpdateCurrentPath(int PathID)
{
	/*
	if (ActivPath[PuthN] == nullptr)
	{
		ActivPath[PuthN] = NewObject<UGeoPath>();
		return;
	}
	ActivPath[PuthN]->AddPoint(GetLastLocation());
	*/
	//UpdateLocationInPath();
	UpdateLocationInPathID(PathID, false);
}

void USpeedup_GeoDataSystem::StopTrackPath(int ItemID, int PathID, int SlotID)
{
	switch (SlotID)
	{
	case 0:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle01) && !HaveActivePath())
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle01);
		}
		break;
	case 1:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle02) && !HaveActivePath())
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle02);
		}
		break;
	case 2:
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle03) && !HaveActivePath())
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle03);
		}
		break;

	default:
		break;
	}

	UpdateLocationInPathID(PathID, true);
	//ActivPath[PuthN]->PointsInPath.Empty();
	//SendFinalPath.Broadcast();

	//StartTrackPathEvent(true, ItemID, PathID, SlotID);
}

void USpeedup_GeoDataSystem::UpdateLocationInPathID(int PathID, bool FinalPath)
{
	FGeoLocationInfo LastLocation = GetLastLocation();
	FGeoPointInfo AddedPoint;
	AddedPoint.PointID = ActivPath[PathID]->PointsInPath.Num();
	AddedPoint.PointLocation = LastLocation.PointLocation;
	AddedPoint.TimeStamp = LastLocation.TimeStamp;
	AddedPoint.DeltaTime = 0.0f;
	AddedPoint.CurrentTime = FDateTime::UtcNow();
	//int64 AAA = FDateTime::UtcNow().ToUnixTimestamp();

	if (ActivPath[PathID]->PathIsActiv == true)
	{
		AddedPoint.PointID = ActivPath[PathID]->PointsInPath.Num();

		if (ActivPath[PathID]->PointsInPath.Num() > 0)
		{
			float DeltaTimePath = 2.0; //(AddedPoint.CurrentTime - ActivPath[PathID]->PointsInPath.Last().CurrentTime).GetSeconds();
			float DeltaLeghtPath = GetDistanse2Coor(ActivPath[PathID]->PointsInPath.Last(), AddedPoint);

			AddedPoint.DeltaTime = DeltaTimePath;
			AddedPoint.PointDistance = DeltaLeghtPath;
			AddedPoint.PointSpeed = DeltaLeghtPath / DeltaTimePath;

			//LeghtPath_Today = LeghtPath_Today + DeltaLeghtPath;
			//LeghtPath_Total = LeghtPath_Total + DeltaLeghtPath;

			ActivPath[PathID]->UserPathInfo.PathLength += DeltaLeghtPath;
			ActivPath[PathID]->UserPathInfo.PathTime += DeltaTimePath;
		}
		else
		{
			AddedPoint.DeltaTime = 0.0f;
			AddedPoint.PointDistance = 0.0f;
			AddedPoint.PointSpeed = -1.0f;

			ActivPath[PathID]->UserPathInfo.PathLength = 0.0f;
			ActivPath[PathID]->UserPathInfo.PathTime = 0.0f;
		}
		ActivPath[PathID]->AddPoint(AddedPoint);
	}

	if ((ActivPath[PathID]->UserPathInfo.PathTime > 60) || (FinalPath))
	{
		float PathSumSpeed = 0.0f;
		float PathMinSpeed = 0.0f;
		float PathMaxSpeed = 0.0f;
		float PathAverageSpeed = 0.0f;
		float PathDistance = 0.0f;

		for (int32 i = 0; i < ActivPath[PathID]->PointsInPath.Num(); ++i)
		{
			if (i == 0)
			{
				PathMinSpeed = ActivPath[PathID]->PointsInPath[i].PointSpeed;
				PathMaxSpeed = ActivPath[PathID]->PointsInPath[i].PointSpeed;
			}
			else
			{
				PathMinSpeed = PathMinSpeed > ActivPath[PathID]->PointsInPath[i].PointSpeed ? ActivPath[PathID]->PointsInPath[i].PointSpeed : PathMinSpeed;
				PathMaxSpeed = PathMaxSpeed < ActivPath[PathID]->PointsInPath[i].PointSpeed ? ActivPath[PathID]->PointsInPath[i].PointSpeed : PathMaxSpeed;
			}
			PathSumSpeed += ActivPath[PathID]->PointsInPath[i].PointSpeed;
		}
		PathAverageSpeed = PathSumSpeed / ActivPath[PathID]->PointsInPath.Num();

		ActivPath[PathID]->UserPathInfo.AverageSpeed = PathSumSpeed / ActivPath[PathID]->PointsInPath.Num();
		ActivPath[PathID]->PointsInPath.Empty();

		FGeoPathinfo AddedPathPart;

		AddedPathPart.PathID = PathID;
		AddedPathPart.AverageSpeed = ActivPath[PathID]->UserPathInfo.AverageSpeed;
		AddedPathPart.PathLength = ActivPath[PathID]->UserPathInfo.PathLength;
		AddedPathPart.PathTime = ActivPath[PathID]->UserPathInfo.PathTime;
		AddedPathPart.maxSpeed = ActivPath[PathID]->UserPathInfo.maxSpeed;
		AddedPathPart.minSpeed = ActivPath[PathID]->UserPathInfo.minSpeed;

		ActivPath[PathID]->PartsOfPath.Add(AddedPathPart);


		//PartsOfPath
		if (FinalPath)
		{
			SendFinalPath.Broadcast(PathID);
		}
		else
		{
			//TestSD.ExecuteIfBound(PathID);
			//TestSD02.Broadcast(PathID);
			//SendPartPath.Broadcast(PathID);

			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->UpdateItem(ActivPath[PathID]->UserPathInfo.ItemID, ActivPath[PathID]->UserPathInfo.PathID, PathDistance, PathAverageSpeed);
			//PathUpdateEvent(0, ItemInfo.);
			//AspeedupGameModeBase* GM = 
			//UpdateDistance(ActivPath[PathID]->UserPathInfo.PathID, ActivPath[PathID]->UserPathInfo.ItemID, ActivPath[PathID]->UserPathInfo.AverageSpeed, ActivPath[PathID]->UserPathInfo.PathLength);
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
void USpeedup_GeoDataSystem::UpdateDistance_Implementation(int DeactivePathID, int DeactivNFDId, int avg_velocity, int avg_distance)
{
}