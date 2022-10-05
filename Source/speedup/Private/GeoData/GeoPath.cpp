#include "..\..\Public\GeoData\GeoPath.h"

void UGeotPoint::SetGeoPointInfo(FGeoPointInfo AddedGeoPointInfo)
{
	PointLocation = AddedGeoPointInfo.PointLocation;
	PointVelosity = AddedGeoPointInfo.PointVelosity;
	CurrentTime = AddedGeoPointInfo.CurrentTime;

}

void UGeoPath::AddPoint(const FGeoPointInfo AddedPoint)
{
	UGeotPoint* NewGeotPoint = NewObject<UGeotPoint>();
	NewGeotPoint->SetGeoPointInfo(AddedPoint);
	PointsInPath.Add(NewGeotPoint);
}

void UGeoPath::AddPointByLocationVelocity(const FVector2D AddedPointLocation, const FVector2D AddedPointVelosity, const int CurrentTime)
{
	FGeoPointInfo NewPoint;
	NewPoint.CurrentTime = CurrentTime;
	//PointInPath->Add(NewPoint);
}

bool UGeoPath::SavePuthInDataTable(FString RowName, UDataTable * DataTable_Puths)
{

	//static ConstructorHelpers::FObjectFinder<UDataTable> valtotextlookup(TEXT("DataTable'/Game/Data/ValToText.ValToText'"));
	//if (valtotextlookup.Object) ValToTextTable = valtotextlookup.Object;
	FGeoPathinfo new_struct;
	new_struct.TotalTime = 100.0;

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
	ResultPoit.CurrentTime = 0.0;
	ResultPoit.PointLocation = FVector2D(0.0, 0.0);
	ResultPoit.PointVelosity = FVector2D(0.0, 0.0);
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
	//if (IndexPoint < PlayerPath.PathLangth)
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
