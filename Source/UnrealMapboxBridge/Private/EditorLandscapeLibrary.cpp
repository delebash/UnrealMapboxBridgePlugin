#include "EditorLandscapeLibrary.h"
#include "LandscapeFileFormatInterface.h"
#include "LandscapeEditorModule.h"
#include <vector>
#include "Misc/Paths.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "LandscapeSubsystem.h"
#include "Editor/LandscapeEditor/Private/LandscapeEdMode.h"


void UEditorLandscapeLibrary::ImportHeightmap(FString FilePath, FString LandscapeName,
                                              FString FileName, const int Width,
                                              const int Height, const int WorldPartitionGridSize)
{
	FilePath += + "\\" + FileName;

	int NewLandscape_QuadsPerSection;
	int NewLandscape_SectionsPerComponent;
	FIntPoint NewLandscape_ComponentCount;

	
	FLandscapeImportHelper::ChooseBestComponentSizeForImport(Width, Height, NewLandscape_QuadsPerSection, NewLandscape_SectionsPerComponent, NewLandscape_ComponentCount);

	const int32 ComponentCountX = NewLandscape_ComponentCount.X;
	const int32 ComponentCountY = NewLandscape_ComponentCount.Y;
	const int32 QuadsPerComponent = NewLandscape_SectionsPerComponent * NewLandscape_QuadsPerSection;
	const int32 SizeX = ComponentCountX * QuadsPerComponent + 1;
	const int32 SizeY = ComponentCountY * QuadsPerComponent + 1;

	
	ALandscape* Landscape = GEditor->GetEditorWorldContext().World()->SpawnActor<ALandscape>();
	Landscape->bCanHaveLayersContent = true;
	
	const auto ActualPath = FilePath.IsEmpty() ? Landscape->ReimportHeightmapFilePath : FilePath;
	if (ActualPath.IsEmpty())
		return;

	//Read png file to height array
	TArray<uint16> RawData;
	ReadHeightmapFile(RawData, *ActualPath, Width, Height);

	// Setup heightmap for landscape
	TMap<FGuid, TArray<uint16>> HeightmapDataPerLayers;
	TMap<FGuid, TArray<FLandscapeImportLayerInfo>> MaterialLayerDataPerLayer;

	// Generate LandscapeActor from heightmap
	HeightmapDataPerLayers.Add(FGuid(), RawData);
	MaterialLayerDataPerLayer.Add(FGuid(), TArray<FLandscapeImportLayerInfo>());

	Landscape->Import(FGuid::NewGuid(), 0, 0, SizeX - 1, SizeY - 1,
		NewLandscape_SectionsPerComponent, NewLandscape_QuadsPerSection, HeightmapDataPerLayers,
		*ActualPath, MaterialLayerDataPerLayer,  ELandscapeImportAlphamapType::Layered);

	ULandscapeInfo* LandscapeInfo = Landscape->GetLandscapeInfo();
	
	Landscape->SetActorLocation(FVector(0, 0, 100));
	Landscape->SetActorScale3D(FVector(100, 100, 100));
	Landscape->SetActorLabel(LandscapeName);
	LandscapeInfo->UpdateLayerInfoMap(Landscape);
	UE_LOG(LogStreaming, Warning, TEXT("%d"), WorldPartitionGridSize);
	if (WorldPartitionGridSize > 0)
	{
		//Setup World partition streaming proxies
		GEditor->GetEditorWorldContext().World()->GetSubsystem<ULandscapeSubsystem>()->ChangeGridSize(LandscapeInfo, WorldPartitionGridSize);
	}
	
}


bool UEditorLandscapeLibrary::ReadHeightmapFile(TArray<uint16>& Result, const FString& Filename, int32 ExpectedWidth,
                                                int32 ExpectedHeight)
{
	bool bResult = true;

	const ILandscapeEditorModule& LandscapeEditorModule = FModuleManager::GetModuleChecked<ILandscapeEditorModule>(
		"LandscapeEditor");
	const ILandscapeHeightmapFileFormat* HeightmapFormat = LandscapeEditorModule.GetHeightmapFormatByExtension(
		*FPaths::GetExtension(Filename, true));

	FLandscapeHeightmapImportData ImportData = HeightmapFormat->Import(*Filename, {
		                                                                   (uint32)ExpectedWidth, (uint32)ExpectedHeight
	                                                                   });
	if (ImportData.ResultCode != ELandscapeImportResult::Error)
	{
		Result = MoveTemp(ImportData.Data);
	}
	else
	{
		UE_LOG(LogStreaming, Warning, TEXT("%s"), *ImportData.ErrorMessage.ToString());
		Result.Empty();
		bResult = false;
	}

	return bResult;
}
