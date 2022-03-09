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
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Landscape")
	static void RunExe(FString PathToExe);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Landscape")
	static void CreateLandscapeFeatures(float CoordinateX, float CoordinateY, float OriginNorthing, float OriginEasting, FString HeightMapDirectory,
													  FString TileHeightmapFileName, int Counter);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Landscape")
	static void ImportHeightmap(FString FilePath, FString LandscapeName,
	                            FString FileName, int LandscapeSize);

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Landscape")
	static void ImportWeightmap(ALandscapeProxy* Landscape, const FString& LayerName,
	                            const FString& FilePath = TEXT(""));

	UFUNCTION(BlueprintCallable, Category = "FolderPicker")
	static void OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath,
	                             FString& OutFolderName);

private:
	static bool ReadHeightmapFile(TArray<uint16>& Result, const FString& Filename, int32 ExpectedWidth,
	                              int32 ExpectedHeight);
	static bool ReadWeightmapFile(TArray<uint8>& Result, const FString& Filename, FName LayerName, int32 ExpectedWidth,
	                              int32 ExpectedHeight);
};
