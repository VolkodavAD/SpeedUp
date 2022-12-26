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
		ActivPath[i]->UserPathInfo.minSpeed = 0.0f;
		ActivPath[i]->UserPathInfo.maxSpeed = 0.0f;
		ActivPath[i]->UserPathInfo.PathLength = 0.0f;
		ActivPath[i]->SetStatusActive(false);
	}

	SaveGeodataMain = Cast<USaveGeodate>(UGameplayStatics::LoadGameFromSlot("LastLocationSlot", 0));
	
	if (SaveGeodataMain)
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		//UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->LastPonitPath01);


		ActivPath[0]->LastPointLocation = SaveGeodataMain->LastPonitPath0;
		ActivPath[1]->LastPointLocation = SaveGeodataMain->LastPonitPath0;
		ActivPath[2]->LastPointLocation = SaveGeodataMain->LastPonitPath0;
	}
}

FGeoLocationInfo USpeedup_GeoDataSystem::GetLastLocation_Implementation()
{
	FGeoLocationInfo CurrentPoint;
	CurrentPoint.PointLocationEnd = FVector2D();
	CurrentPoint.TimeStamp = 0.0f;
	return CurrentPoint;
}

float USpeedup_GeoDataSystem::GetDistanse2Coor_Implementation(FVector2D PointStart, FVector2D PointEnd)
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
	// The operation was successful, so LoadedGame now contains the data we saved earlier.
	//UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->LastPonitPath01);


	//ActivPath[0]->LastPointLocation = LoadedGame->LastPonitPath01;
	//ActivPath[1]->LastPointLocation = LoadedGame->LastPonitPath02;
	//ActivPath[2]->LastPointLocation = LoadedGame->LastPonitPath03;

	ReInitServis();

	//USaveGeodate* LoadedGame = Cast<USaveGeodate>(UGameplayStatics::LoadGameFromSlot("LastLocationSlot", 0));
	

	if (SaveGeodataMain)
	{
		FGeoPointInfo AddedPoint;
		AddedPoint.PointID = 0;
		AddedPoint.DeltaTime = 0.0f;

		switch (SlotID)
		{
		case 0:
			AddedPoint.PointLocationEnd = SaveGeodataMain->LastPonitPath0.PointLocationEnd;
			AddedPoint.TimeStamp = SaveGeodataMain->LastPonitPath0.TimeStamp;
			AddedPoint.CurrentTime = FDateTime::FromUnixTimestamp((int64)SaveGeodataMain->LastPonitPath0.TimeStamp);
			break;
		case 1:
			AddedPoint.PointLocationEnd = SaveGeodataMain->LastPonitPath0.PointLocationEnd;
			AddedPoint.TimeStamp = SaveGeodataMain->LastPonitPath0.TimeStamp;
			AddedPoint.CurrentTime = FDateTime::FromUnixTimestamp((int64)SaveGeodataMain->LastPonitPath0.TimeStamp);
			break;
		case 2:
			AddedPoint.PointLocationEnd = SaveGeodataMain->LastPonitPath0.PointLocationEnd;
			AddedPoint.TimeStamp = SaveGeodataMain->LastPonitPath0.TimeStamp;
			AddedPoint.CurrentTime = FDateTime::FromUnixTimestamp((int64)SaveGeodataMain->LastPonitPath0.TimeStamp);
			break;
		}

		ActivPath[SlotID]->PointsInPath.Add(AddedPoint);
	}


	//if (ServiceEnable && ServiceInit)
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

void USpeedup_GeoDataSystem::StartTrackPath(int ItemID, int PathID, int SlotID)
{
	ReInitServis();
	//if ((ServiceEnable && ServiceInit))
	{
		ActivPath[SlotID] = NewObject<UGeoPath>();
		ActivPath[SlotID]->SetSlotID(SlotID);
		ActivPath[SlotID]->SetPathID(PathID);
		ActivPath[SlotID]->SetItemID(ItemID);
		ActivPath[SlotID]->SetStatusActive(true);

		USaveGeodate* LoadedGame = Cast<USaveGeodate>(UGameplayStatics::LoadGameFromSlot("LastLocationSlot", 0));

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
	UpdateNum++;

	if (ActivPath[SlotN]->PathIsActiv == true)
	{
		FGeoLocationInfo LastLocation = GetLastLocation();

		FGeoPointInfo AddedPoint;

		AddedPoint.CurrentTime = FDateTime::UtcNow();
		AddedPoint.DeltaTime = 0.0f;
		AddedPoint.PointSpeed = 0.0f;
		AddedPoint.PointDistance = 0.0f;
		AddedPoint.PointID = ActivPath[SlotN]->PointsInPath.Num();
		AddedPoint.PointLocationEnd = LastLocation.PointLocationEnd;
		AddedPoint.TimeStamp = LastLocation.TimeStamp;

		if (UKismetMathLibrary::Abs(AddedPoint.PointLocationEnd.X) > 0.001 && UKismetMathLibrary::Abs(AddedPoint.PointLocationEnd.X) > 0.001)
		{

			if (ActivPath[SlotN]->PointsInPath.Num() == 0)
			{
				/*
				FGeoPointInfo AddedFirstPointPoint;

				AddedFirstPointPoint.CurrentTime = FDateTime::UtcNow();
				AddedFirstPointPoint.PointID = ActivPath[SlotN]->PointsInPath.Num();
				AddedFirstPointPoint.PointLocationEnd = LastLocation.PointLocationEnd;

				AddedFirstPointPoint.PointDistance = 0.0f;
				AddedFirstPointPoint.PointSpeed = 0.0f;
				AddedFirstPointPoint.DeltaTime = 0.0f;
				AddedFirstPointPoint.TimeStamp = ActivPath[SlotN]->LastPointLocation.TimeStamp;
				*/

				ActivPath[SlotN]->AddPoint(AddedPoint);
			}
			else
			{
				//DeltaTimePath = 2.0; //(AddedPoint.CurrentTime - ActivPath[PathID]->PointsInPath.Last().CurrentTime).GetSeconds();
				float DeltaLeghtPath = GetDistanse2Coor(ActivPath[SlotN]->PointsInPath.Last().PointLocationEnd, LastLocation.PointLocationEnd);

				float DT1 = LastLocation.TimeStamp - ActivPath[SlotN]->LastPointLocation.TimeStamp;
				float DT = LastLocation.TimeStamp - ActivPath[SlotN]->PointsInPath.Last().TimeStamp;

				AddedPoint.DeltaTime = DT;
				//AddedPoint.DeltaTime = UKismetMathLibrary::Abs(DeltaTimePath);
				
				AddedPoint.PointDistance = DeltaLeghtPath;
				AddedPoint.PointSpeed = (DeltaLeghtPath / DT) * 3600;

				ActivPath[SlotN]->UserPathInfo.PathLength += DeltaLeghtPath;
				ActivPath[SlotN]->UserPathInfo.PathTime += DT;

				ActivPath[SlotN]->LastPointLocation = LastLocation;
				ActivPath[SlotN]->AddPoint(AddedPoint);
			}

			ActivPath[SlotN]->LastPointLocation = LastLocation;

			if (USaveGeodate* SaveGameInstance = Cast<USaveGeodate>(UGameplayStatics::CreateSaveGameObject(USaveGeodate::StaticClass())))
			{
				SaveGameInstance->PlayerName = TEXT("PlayerOne");
				SaveGameInstance->HaveSave = true;
				SaveGameInstance->LastPonitPath0 = ActivPath[0]->LastPointLocation;

				if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, "LastLocationSlot", 0))
				{
					// Save succeeded.
				}
			}
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
			PathSumSpeed += UKismetMathLibrary::Abs(ActivPath[SlotN]->PointsInPath[i].PointSpeed);
			PathDistance += UKismetMathLibrary::Abs(ActivPath[SlotN]->PointsInPath[i].PointDistance);
		}
		if (ActivPath[SlotN]->PointsInPath.Num() > 0.0f)
		{
			PathAverageSpeed = PathSumSpeed / ActivPath[SlotN]->PointsInPath.Num();
		}
		else
		{
			PathAverageSpeed = 0.0f;
		}

		ActivPath[SlotN]->PartsOfPath.Add(ActivPath[SlotN]->UserPathInfo);

		if (FinalPath)
		{
			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->FinalPathItem(ActivPath[SlotN]->UserPathInfo.ItemID, ActivPath[SlotN]->UserPathInfo.PathID, SlotN, ActivPath[SlotN]->UserPathInfo.PathLength, ActivPath[SlotN]->UserPathInfo.AverageSpeed);
		}
		else
		{
			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->UpdatePathItem(ActivPath[SlotN]->UserPathInfo.ItemID, ActivPath[SlotN]->UserPathInfo.PathID, ActivPath[SlotN]->UserPathInfo.PathLength, ActivPath[SlotN]->UserPathInfo.AverageSpeed);
		}

		ActivPath[SlotN]->PointsInPath.Empty();
		ActivPath[SlotN]->UserPathInfo.PathTime = 0.0f;
		ActivPath[SlotN]->UserPathInfo.PathLength = 0.0f;
		ActivPath[SlotN]->UserPathInfo.maxSpeed = 0.0f;
		ActivPath[SlotN]->UserPathInfo.minSpeed = 0.0f;
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