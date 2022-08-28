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


/*
bool UGeoPath::GetPoint(int IndexPoint, FMovePoint& ResultPoit)
{
	ResultPoit.CurrentTime = 0;
	ResultPoit.PointLocation = 0.0;
	ResultPoit.PointVelosity = 0.0;
	return false;
}
*/
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
