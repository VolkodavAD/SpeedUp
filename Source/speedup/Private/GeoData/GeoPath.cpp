#include "..\..\Public\GeoData\GeoPath.h"

void UGeotPoint::SetGeoPointInfo(FGeoPointInfo AddedGeoPointInfo)
{
	PointLocation = AddedGeoPointInfo.PointLocation;
	PointVelosity = AddedGeoPointInfo.PointVelosity;
	CurrentTime = AddedGeoPointInfo.CurrentTime;
}

FGeoPointInfo UGeotPoint::GetGeoPointInfo()
{
	FGeoPointInfo ReturnedGeoPoints;
	ReturnedGeoPoints.PointID = PointID;
	ReturnedGeoPoints.PointLocation = PointLocation;
	ReturnedGeoPoints.PointVelosity = PointVelosity;
	ReturnedGeoPoints.CurrentTime = CurrentTime;

	return ReturnedGeoPoints;
}

void UGeoPath::AddPoint(const FGeoPointInfo AddedPoint)
{
	UGeotPoint* NewGeotPoint = NewObject<UGeotPoint>();
	NewGeotPoint->SetGeoPointInfo(AddedPoint);
	PlayerPathInfo.PointsInPath.Add(NewGeotPoint->GetGeoPointInfo());
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
	FGeoPathinfo new_struct;
	new_struct.PathLength = 100.0;

	FGeoPointInfo AddedRow;
	AddedRow.Name = "A1";

	new_struct = this->PlayerPathInfo;
	if (DataTable_Puths->IsValidLowLevel())
	{
		DataTable_Puths->AddRow(FName(RowName), new_struct);
		//DataTable_Puths->AddRow("test_item_insert2", new_struct);

		//DataTable_Puths->AddRow(FName("001"), AddedRow); 
		//DataTable_Puths->Row
	}
	return false;
}

bool UGeoPath::GetPoint(int IndexPoint, UGeotPoint& ResultPoit)
{
	FDateTime DefaultDT;
	ResultPoit.PointID = 0;
	ResultPoit.CurrentTime = DefaultDT;
	ResultPoit.PointLocation = FVector2D(0.0f, 0.0f);
	ResultPoit.PointVelosity = 0.0f;
	return false;

	//FGeoPointInfo AddedRow;
	//AddedRow.Name = "A1";
	//DataTable_Puths.AddRow(FName("001"), AddedRow);
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
