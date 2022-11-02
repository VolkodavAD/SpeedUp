// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoData/Speedup_GeoDataSystem.h"
#include "Engine.h"
#include "Misc/DateTime.h"
//#include "Logging/LogMacros.h"
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
	SetComponentTickEnabled(false);
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

	for (int32 i = 0; i < ActivPath.Num(); ++i)
	{
		ActivPath[i] = NewObject<UGeoPath>();
	}
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

void USpeedup_GeoDataSystem::StartTrackPath(int PuthN)
{
	if ((PuthN < 0) && (PuthN > 2))
	return;

	ReInitServis();

	UE_LOG(LogTemp, Warning, TEXT("ServiceEnable : %d"), ServiceEnable);

	if (PathTimerHandle.IsValid())
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("PathTimerHandle.IsValid - true")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("PathTimerHandle.IsValid - false")));

	if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle))
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("IsTimerActive - true")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Silver, FString::Printf(TEXT("IsTimerActive - false")));

	if (!GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle))
	{
		//PathTimerHandle.IsValid() ? STR_IsValid = "STR_IsValid is valid": STR_IsValid = "STR_IsValid is not valid";

		//UE_LOG(LogTemp, Warning, TEXT("PathTimerHandle.IsValid : %d"), PathTimerHandle.IsValid());
		//UE_LOG(LogTemp, Warning, TEXT("IsTimerActive : %s"), GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle))
		//GetWorld()->GetTimerManager().SetTimer(PathTimerHandle, this, &USpeedup_GeoDataSystem::UpdateLocation, 6.0f, true, 2.0f);
	}

	if (ActivPath[PuthN] == nullptr)
	{
		ActivPath[PuthN] = NewObject<UGeoPath>();
	}
	ActivPath[PuthN]->SetStatusActive(true);

	switch (PuthN)
	{
	case 0:
		TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 0);
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle01, TimerDelegatePuth01, 6.0f, true, 0.1f);

		break;
	case 1:
		TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 1);
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle02, TimerDelegatePuth02, 6.0f, true, 0.1f);
		break;
	case 2:
		TimerDelegatePuth01.BindUFunction(this, FName("UpdateCurrentPath"), 2);
		GetWorld()->GetTimerManager().SetTimer(PathTimerHandle03, TimerDelegatePuth03, 6.0f, true, 0.1f);
		break;

	default:
		break;
	}

	//GetWorld()->GetTimerManager().SetTimer(PathTimerHandle, this, &USpeedup_GeoDataSystem::UpdateLocationInPath, 6.0f, true, 2.0f);
	ActivPath[PuthN]->PathIsActiv = true;
}

void USpeedup_GeoDataSystem::UpdateCurrentPath(int PuthN)
{
	/*
	if (ActivPath[PuthN] == nullptr)
	{
		ActivPath[PuthN] = NewObject<UGeoPath>();
		return;
	}
	ActivPath[PuthN]->AddPoint(GetLastLocation());
	*/
	UpdateLocationInPath();

}

void USpeedup_GeoDataSystem::StopTrackPath(int PuthN)
{
	switch (PuthN)
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

	/*
	if (PathTimerHandle.IsValid())
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(PathTimerHandle) && !HaveActivePath())
		{
			GetWorld()->GetTimerManager().ClearTimer(PathTimerHandle);
		}
	}
	*/

	ActivPath[PuthN]->PointsInPath.Empty();
}

void USpeedup_GeoDataSystem::UpdateLocationInPath()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("UpdateLocationInPath")));

	FGeoPointInfo AddedPoint = GetLastLocation();

	for (int32 i = 0; i < ActivPath.Num(); ++i)
	{
		if (ActivPath[i]->PathIsActiv == true)
		{
			AddedPoint.PointID = ActivPath[i]->PointsInPath.Num();
			if (ActivPath[i]->PointsInPath.Num() > 0)
			{
				float DeltaTimePath = (AddedPoint.CurrentTime - ActivPath[i]->PointsInPath.Last().CurrentTime).GetSeconds();
				float DeltaLeghtPath = GetDistanse2Coor(ActivPath[i]->PointsInPath.Last(), AddedPoint);
				
				AddedPoint.PointVelosity = DeltaLeghtPath / DeltaTimePath;
				AddedPoint.PointDistance = DeltaLeghtPath;
				AddedPoint.DeltaTime = 0.0f;

				LeghtPath_Today = LeghtPath_Today + DeltaLeghtPath;
				LeghtPath_Total = LeghtPath_Total + DeltaLeghtPath;
			}
			else
			{
				AddedPoint.PointVelosity = -1.0f;
				AddedPoint.PointDistance = 0.0f;
				AddedPoint.DeltaTime  = 0.0f;
			}
			ActivPath[i]->AddPoint(AddedPoint);
		}
	}

	/*
	AddedPoint.PointID = LastSneakersPathID++;
	if (ActivSneakersPath->UserPathInfo.PointsInPath.Num() != 0)
	{
		float DeltaTimePath = (AddedPoint.CurrentTime - ActivSneakersPath->UserPathInfo.PointsInPath.Last().CurrentTime).GetSeconds();
		float DeltaLeghtPath = GetDistanse2Coor(ActivSneakersPath->UserPathInfo.PointsInPath.Last(), AddedPoint);
		AddedPoint.PointVelosity = DeltaLeghtPath / DeltaTimePath;
	}
	else
	{
		AddedPoint.PointVelosity = -1.0;
	}
	ActivSneakersPath->AddPoint(AddedPoint);
	*/
}

void USpeedup_GeoDataSystem::UpdateLocationInPathID(int PathID)
{
	FGeoPointInfo AddedPoint = GetLastLocation();
	if (ActivPath[PathID]->PathIsActiv == true)
	{
		AddedPoint.PointID = ActivPath[PathID]->PointsInPath.Num();
		if (ActivPath[PathID]->PointsInPath.Num() > 0)
		{
			float DeltaTimePath = (AddedPoint.CurrentTime - ActivPath[PathID]->PointsInPath.Last().CurrentTime).GetSeconds();
			float DeltaLeghtPath = GetDistanse2Coor(ActivPath[PathID]->PointsInPath.Last(), AddedPoint);
			
			AddedPoint.PointDistance = DeltaLeghtPath;
			AddedPoint.PointVelosity = DeltaLeghtPath / DeltaTimePath;

			LeghtPath_Today = LeghtPath_Today + DeltaLeghtPath;
			LeghtPath_Total = LeghtPath_Total + DeltaLeghtPath;
		}
		else
		{
			AddedPoint.PointVelosity = -1.0;
		}
		
		ActivPath[PathID]->AddPoint(AddedPoint);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("UpdateLocation")));
	UpdateLocationInPath();
}

//FTimerDelegate TimerDel;
//FTimerHandle TimerHandle;

//int32 MyInt = 10;
//float MyFloat = 20.f;

//Binding the function with specific values
//TimerDel.BindUFunction(this, FName("MyUsefulFunction"), MyInt, MyFloat);
//Calling MyUsefulFunction after 5 seconds without looping
//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 5.f, false);


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