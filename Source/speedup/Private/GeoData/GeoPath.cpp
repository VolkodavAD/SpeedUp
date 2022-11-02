//#include "LocationServicesBPLibrary.h"
#include "..\..\Public\GeoData\GeoPath.h"

void UGeotPoint::SetGeoPointInfo(FGeoPointInfo AddedGeoPointInfo)
{
	Pointinfo = AddedGeoPointInfo;
	//Pointinfo.PointID = AddedGeoPointInfo.PointID;
	//Pointinfo.PointLocation = AddedGeoPointInfo.PointLocation;
	//Pointinfo.PointVelosity = AddedGeoPointInfo.PointVelosity;
	//Pointinfo.CurrentTime = AddedGeoPointInfo.CurrentTime;
	//Pointinfo.PointDistance = AddedGeoPointInfo.PointDistance;
}

FGeoPointInfo UGeotPoint::GetGeoPointInfo()
{
	FGeoPointInfo ReturnedGeoPoints;
	ReturnedGeoPoints.PointID = Pointinfo.PointID;
	ReturnedGeoPoints.PointLocation = Pointinfo.PointLocation;
	ReturnedGeoPoints.PointVelosity = Pointinfo.PointVelosity;
	ReturnedGeoPoints.CurrentTime = Pointinfo.CurrentTime;

	return ReturnedGeoPoints;
}
// ------------------------------------------------------------------------PATH ---------------------------------------------------
void UGeoPath::SetStatusActive(bool NewStatusActive)
{
	PathIsActiv = NewStatusActive;
}
bool UGeoPath::GetStatusActive()
{
	return PathIsActiv;
}


void UGeoPath::AddPoint(const FGeoPointInfo AddedPoint)
{
	//FGeoPointInfo PreviewPointInfo = UserPathInfo.PointsInPath.Last();

	UGeotPoint* NewGeotPoint = NewObject<UGeotPoint>();
	NewGeotPoint->SetGeoPointInfo(AddedPoint);
	//NewGeotPoint->PointDistance = DistanceBet
	PointsInPath.Add(NewGeotPoint->GetGeoPointInfo());
	UserPathInfo.PathLength += AddedPoint.PointDistance;
	//UserPathInfo.FDateTime += AddedPoint;
}

void UGeoPath::AddPointByLocationVelocity(const int AddedPointID, const FVector2D AddedPointLocation, const float AddedPointVelosity, const FDateTime CurrentTime)
{
	FGeoPointInfo NewPoint;
	NewPoint.PointID = AddedPointID;
	NewPoint.PointLocation = AddedPointLocation;
	NewPoint.PointVelosity = AddedPointVelosity;
	NewPoint.CurrentTime = CurrentTime;

	AddPoint(NewPoint);
}

bool UGeoPath::SavePuthInDataTable(FString RowName, UDataTable* DataTable_Puths)
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> valtotextlookup(TEXT("DataTable'/Game/Data/ValToText.ValToText'"));
	//if (valtotextlookup.Object) ValToTextTable = valtotextlookup.Object;
	int32 NewRawName = FCString::Atoi(*DataTable_Puths->GetRowNames().Last().ToString());

	FGeoPathinfo new_struct;
	FGeoPointInfo AddedRow;
	AddedRow.Name = "A1";

	new_struct = this->UserPathInfo;
	if (DataTable_Puths->IsValidLowLevel())
	{
		DataTable_Puths->AddRow(FName(FString::FromInt(NewRawName)), new_struct);
		//DataTable_Puths->AddRow("test_item_insert2", new_struct);
		// 
		//DataTable_Puths->AddRow(FName("001"), AddedRow); 
		//DataTable_Puths->Row
	}
	return false;
}

/*
FMovePoint* UGeoPath::GetPoint(int IndexPoint)
{
	return nullptr;
}
*/

/*
FMovePoint UGeoPath::GetPoint(int IndexPoint)
{
	//if (IndexPoint < PlayerPath.PathLength)
	return PlayerPath.PointInPath[IndexPoint];
}
FMovePoint UGeoPath::GetPoint(int IndexPoint)
{
	if (IndexPoint < PlayerPath.PointInPath)
		return PlayerPath.PointInPath[IndexPoint];
	else
		return null;
}
*/
