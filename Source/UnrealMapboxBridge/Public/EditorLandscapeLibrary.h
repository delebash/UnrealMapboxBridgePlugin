#pragma once

#include "CoreUObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorLandscapeLibrary.generated.h"


class ALandscape;
class ALandscapeProxy;

UCLASS(Blueprintable)
class UNREALMAPBOXBRIDGE_API UEditorLandscapeLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Dan Editor Scripting | Landscape")
	static void ImportHeightmap(FString FilePath, FString LandscapeName,
							FString FileName, const int Width, const int Height,const int WorldPartitionGridSize);

private:
	static bool ReadHeightmapFile(TArray<uint16>& Result, const FString& Filename, int32 ExpectedWidth,
	                              int32 ExpectedHeight);
};
