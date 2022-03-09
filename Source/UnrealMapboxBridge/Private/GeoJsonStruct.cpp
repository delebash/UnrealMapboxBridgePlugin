#include "GeoJsonStruct.h"

FGeoJsonStruct FGeoJsonStruct::BuildGeoJsonStruct(
	FString GeometryType,
	FString Type
//	TArray<FVector> GeometryCoordinates
)
{
	FGeoJsonStruct FGeoJsonStruct;
	FGeoJsonStruct.GeometryType = GeometryType;
	FGeoJsonStruct.Type = Type;
//	FGeoJsonStruct.GeometryCoordinates = GeometryCoordinates;
	return FGeoJsonStruct;
}
