#pragma once

#include "GeoJsonStruct.generated.h"

USTRUCT(BlueprintType)
struct FGeoJsonStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "GeoJson")
	FString GeometryType;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "GeoJson")
	FString Type;

	// UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "GeoJson")
	// TArray<FVector> GeometryCoordinates;

public:
	static FGeoJsonStruct BuildGeoJsonStruct(
		FString GeometryType,
		FString Type
	//	TArray<FVector> GeometryCoordinates
	);
};

//
// UPROPERTY()
// FJsonObject properties;
//
// UPROPERTY()
// FJsonObject layer;
//
// UPROPERTY()
// FString source;
//
// UPROPERTY()
// FJsonObject state;
