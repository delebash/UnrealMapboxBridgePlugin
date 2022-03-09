#include "EditorLandscapeLibrary.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Landscape.h"
#include "LandscapeProxy.h"
#include "LandscapeInfo.h"
#include "LandscapeEdit.h"
#include "LandscapeEditorUtils.h"
#include "Foliage/Public/InstancedFoliageActor.h"
#include "LandscapeSplinesComponent.h"
#include "Editor.h"
#include "LandscapeFileFormatInterface.h"
#include "LandscapeEditorModule.h"
#include "Components/SplineComponent.h"
#include <string>
// #include <iostream>
// #include <istream>
// #include "JsonUtilities.h"
#include "EditorAssetLibrary.h"
#include <vector>
#include  <nlohmann/json.hpp>
#include "Misc/Paths.h"
#include "Interfaces/IPluginManager.h"


#include <fstream>
#include "UObject/ConstructorHelpers.h"
#include "Components/SplineComponent.h"


using json = nlohmann::json;

void UEditorLandscapeLibrary::RunExe(const FString PathToExe)
{
	static FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("UnrealMapboxBridge"))->GetBaseDir();
	FString AppExePath = BaseDir +
		"\\Resources\\unreal_mapbox_bridge.exe";
	const TCHAR* charPathToExe = *AppExePath;
	FPlatformProcess::CreateProc(charPathToExe, nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
}

void UEditorLandscapeLibrary::OpenFolderDialog(const FString& DialogTitle, const FString& DefaultPath,
                                               FString& OutFolderName)
{
	{
		if (GEngine)
		{
			//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
			IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
			if (DesktopPlatform)
			{
				DesktopPlatform->OpenDirectoryDialog(NULL, DialogTitle, DefaultPath, OutFolderName);
			}
		}
	}
}

void UEditorLandscapeLibrary::CreateLandscapeFeatures(float CoordinateX, float CoordinateY, float OriginNorthing,
                                                      float OriginEasting,
                                                      FString HeightMapDirectory,
                                                      FString TileHeightmapFileName, int Counter)
{
	//17250.0 x
	//13040.0
	UE_LOG(LogNet, Log, TEXT("Utmx: %f"), CoordinateX);
	UE_LOG(LogNet, Log, TEXT("Utmy: %f"), CoordinateY);
	UE_LOG(LogNet, Log, TEXT("OriginNorthing: %f"), OriginNorthing);
	UE_LOG(LogNet, Log, TEXT("OriginEasting: %f"), OriginEasting);

	float xx = (CoordinateX - OriginNorthing) * 100.0;
	float yy = (OriginEasting - CoordinateY) * 100.0;
	UE_LOG(LogNet, Log, TEXT("xx: %f"), xx);
	UE_LOG(LogNet, Log, TEXT("yy: %f"), yy);
	FVector SpawnLocation = FVector(xx, yy, 0);
	FRotator SpawnRotation = FRotator(0.0, 0.0, 0.0);

	UBlueprint* blueprint = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), NULL,
	                                                          TEXT(
		                                                          "Blueprint'/UnrealMapboxBridge/Blueprints/ImportLines.ImportLines'")));
	TSubclassOf<AActor> BPToSpawn = (UClass*)(blueprint->GeneratedClass);
	if (BPToSpawn != NULL)
	{
		UE_LOG(LogNet, Log, TEXT("I got class"))
		UE_LOG(LogNet, Log, TEXT("BName: %s"), *BPToSpawn->GetClass()->GetName());
	}
	else
	{
		UE_LOG(LogNet, Log, TEXT("I got nothing"));
	}


	USplineComponent* SplineComponent;
	FActorSpawnParameters parameters = FActorSpawnParameters();
	parameters.ObjectFlags = RF_NoFlags;

	UWorld* World = GEditor->GetEditorWorldContext().World();

	AActor* actorObject = World->SpawnActor<AActor>(BPToSpawn, SpawnLocation, SpawnRotation, parameters);
	USceneComponent* RootComponent = actorObject->GetRootComponent();
	SplineComponent = Cast<USplineComponent>(RootComponent->GetChildComponent(1));


	if (Counter == 0)
	{
		SplineComponent->ClearSplinePoints();
	}

	SplineComponent->AddSplinePointAtIndex(SpawnLocation, Counter, ESplineCoordinateSpace::Type::World);
	SplineComponent->SetSplinePointType(Counter, ESplinePointType::Type::CurveClamped, true);
}


void UEditorLandscapeLibrary::ImportHeightmap(FString FilePath, FString LandscapeName,
                                              FString FileName, int LandscapeSize)
{
	FilePath += + "\\" + FileName;

	ALandscape* Landscape = GEditor->GetEditorWorldContext().World()->SpawnActor<ALandscape>();

	int ComponentSizeQuads = 63;
	int SubsectionSizeQuads = 63;
	int NumSubsections = 2;

	Landscape->ComponentSizeQuads = ComponentSizeQuads;
	Landscape->SubsectionSizeQuads = SubsectionSizeQuads;
	Landscape->NumSubsections = NumSubsections;
	Landscape->SetLandscapeGuid(FGuid::NewGuid());

	const auto ActualPath = FilePath.IsEmpty() ? Landscape->ReimportHeightmapFilePath : FilePath;
	if (ActualPath.IsEmpty())
		return;

	//Read png file to height array
	TArray<uint16> RawData;
	ReadHeightmapFile(RawData, *ActualPath, LandscapeSize, LandscapeSize);

	// Setup heightmap for landscape
	TMap<FGuid, TArray<uint16>> HeightmapDataPerLayers;
	TMap<FGuid, TArray<FLandscapeImportLayerInfo>> MaterialLayerDataPerLayer;

	// Generate LandscapeActor from heightmap
	HeightmapDataPerLayers.Add(FGuid(), RawData);
	MaterialLayerDataPerLayer.Add(FGuid(), TArray<FLandscapeImportLayerInfo>());

	Landscape->Import(Landscape->GetLandscapeGuid(), 0, 0, LandscapeSize - 1,
	                  LandscapeSize - 1, Landscape->NumSubsections, Landscape->SubsectionSizeQuads,
	                  HeightmapDataPerLayers,
	                  TEXT("NONE"), MaterialLayerDataPerLayer, ELandscapeImportAlphamapType::Layered
	);

	Landscape->SetActorLocation(FVector(0, 0, 100));
	Landscape->SetActorScale3D(FVector(100, 100, 100));
	Landscape->CreateLandscapeInfo();
	Landscape->SetActorLabel(LandscapeName);
}

void UEditorLandscapeLibrary::ImportWeightmap(ALandscapeProxy* Landscape, const FString& LayerName,
                                              const FString& FilePath /*= TEXT("")*/)
{
	const FName LayerName_ = FName(*LayerName);
	for (auto& LayerSettings : Landscape->EditorLayerSettings)
	{
		if (LayerSettings.LayerInfoObj && (LayerSettings.LayerInfoObj->LayerName == LayerName_))
		{
			auto ActualPath = FilePath.IsEmpty() ? LayerSettings.ReimportLayerFilePath : FilePath;
			if (ActualPath.IsEmpty())
				return;

			auto LandscapeSize = Landscape->GetBoundingRect();
			int32 NumSamplesX = LandscapeSize.Width() + 1;
			int32 NumSamplesY = LandscapeSize.Height() + 1;

			TArray<uint8> RawData;
			ReadWeightmapFile(RawData, *ActualPath, LayerSettings.LayerInfoObj->LayerName, NumSamplesX, NumSamplesY);
			//LandscapeEditorUtils::SetWeightmapData(Landscape, LayerSettings.LayerInfoObj, RawData);

			FVector LandscapeOrigin;
			FVector LandscapeBounds;
			Landscape->GetActorBounds(false, LandscapeOrigin, LandscapeBounds);
			Landscape->SetActorLocation(FVector(0, 0, LandscapeBounds.Z));
		}
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

bool UEditorLandscapeLibrary::ReadWeightmapFile(TArray<uint8>& Result, const FString& Filename, FName LayerName,
                                                int32 ExpectedWidth, int32 ExpectedHeight)
{
	bool bResult = true;

	const ILandscapeEditorModule& LandscapeEditorModule = FModuleManager::GetModuleChecked<ILandscapeEditorModule>(
		"LandscapeEditor");
	const ILandscapeWeightmapFileFormat* WeightmapFormat = LandscapeEditorModule.GetWeightmapFormatByExtension(
		*FPaths::GetExtension(Filename, true));

	FLandscapeWeightmapImportData ImportData = WeightmapFormat->Import(*Filename, LayerName, {
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


// /* Find the blueprint of the 3D model */
// UBlueprint* blueprint = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/UnrealMapboxBridge/Blueprints/ImportLines.ImportLines'")));
// TSubclassOf<class UObject> MyItemBlueprint = (UClass*)(blueprint->GeneratedClass);
// if (MyItemBlueprint != NULL) {
// 	UE_LOG(LogNet, Log, TEXT("I got class"))
// 	UE_LOG(LogNet, Log, TEXT("BName: %s"), *MyItemBlueprint->GetClass()->GetName());
// } else {
// 	UE_LOG(LogNet, Log, TEXT("I got nothing"));
// }

// USceneComponent* SceneComponent;
//AmySphere* mySphere =  GetWorld()->SpawnActor<AmySphere>(MyItemBlueprint::StaticClass(), myLoc, myRot, SpawnInfo);

// ChildSceneComponent = 
//  CreateDefaultSubobject<USceneComponent>
//  ("ChildSceneComponent");

// TSubclassOf<AActor> spawnedClass;
//
// // This string is obtained by right clicking the asset in the content browser and selecting "CopyReference", then pasting in a text file.
// FString spawnedBlueprintReference = TEXT("Blueprint'/Game/FirstPersonCPP/Blueprints/FirstPersonProjectile.FirstPersonProjectile'");
//    
// UObject* loadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *spawnedBlueprintReference);
//    
// UBlueprint* castedBlueprint = Cast<UBlueprint>(someObject);
//    
// if (castedBlueprint && castedBlueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
// {
// 	// Don't forget the asterisk
// 	spawnedClass = *castedBlueprint->GeneratedClass;
// }


// UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/DEXIED/Foliage/Tree/BP_TreeDestroyed_Style_1.BP_TreeDestroyed_Style_1")));
//
// UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
// if (!SpawnActor)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
// 	return;
// }
//
// UClass* SpawnClass = SpawnActor->StaticClass();
// if (SpawnClass == NULL)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
// 	return;
// }
//
// UWorld* World = GetWorld();
// FActorSpawnParameters SpawnParams;
// SpawnParams.Owner = this;
// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

// importlines = unreal.EditorAssetLibrary().load_blueprint_class('/Game/ImportLines')

// xx = (float(coord[0]) - UTMx) * 100.0
// 	 yy = (UTMy - float(coord[1])) * 100.0
// 	 nv = unreal.Vector(x=xx, y=yy, z=zvalue)
// 	 if pi == 0:
// 		 rt = unreal.Rotator(roll=0.0, pitch=0.0, yaw=0.0)
// 		 actorObject = ed.spawn_actor_from_class(importlines, nv, rt, transient=False)
// 		 SceneComponent = actorObject.root_component
// 		 SplineComponent = SceneComponent.get_child_component(1)
// 		 SplineComponent.clear_spline_points()
// 	 SplineComponent.add_spline_point_at_index(nv, pi, unreal.SplineCoordinateSpace.WORLD)
// 	 SplineComponent.set_spline_point_type(pi, SplinePointType, update_spline=True)


// UE_LOG(LogTemp, Warning, TEXT("%s"), *HeightMapDirectory)


// range-based for
// for (auto& element : j) {
// 	std::cout << element << '\n';
// }


// iterate the array
// for (json::iterator it = j.begin(); it != j.end(); ++it) {
// 	GLog->Log("Test");
// 	 std::cout  << *it << '\n';
// }

// range-based for
// for (auto& element : j) {
// 	GLog->Log("Test");
// 	std::cout << element << '\n';
// }
// GLog->Log(j.items());

// for (auto& elm : j.items())
// {
// nlohmann::json object = elm.value();
//
// string type;
// int32 id;
// string sourceLayer;
// string source;
//
// string Geotype = object.at("geometry")["type"];
//
// nlohmann::json GeoArrycoordinates = object.at("geometry")["coordinates"];
//
// if (object.contains("type"))
// {
// 	type = object.at("type");
// }
// nlohmann::json Objproperties = object.at("properties");
//
// if (object.contains("id"))
// {
// 	id = object.at("id");
// }
//
// nlohmann::json Objlayer = object.at("layer");
//
// if (object.contains("sourceLayer"))
// {
// 	sourceLayer = object.at("sourceLayer");
// }
//
// if (object.contains("source"))
// {
// 	source = object.at("source");
// }
//
// nlohmann::json Objstate = object.at("state");
//
//
// if (Geotype == "LineString")
// {
// 	GLog->Log("LineString");
// 	// JsonCoordinatesArray = Coordinates[1]->AsArray();
// }
// }


// Latitude is denoted by Y (northing) and Longitude by X (Easting)

// 	SplinePointType = unreal.SplinePointType.CURVE_CLAMPED
// # SplinePointType = unreal.SplinePointType.CURVE_CUSTOM_TANGENT
// # SplinePointType = unreal.SplinePointType.LINEAR
// # SplinePointType = unreal.SplinePointType.CURVE
// # SplinePointType = unreal.SplinePointType.CONSTANT
// 	
// 	xx = (float(coord[0]) - UTMx) * 100.0
// 		   yy = (UTMy - float(coord[1])) * 100.0
//
// 	nv = unreal.Vector(x=xx, y=yy, z=zvalue)
// 	if ()
// 	{
// 		rt = unreal.Rotator(roll=0.0, pitch=0.0, yaw=0.0)
// 			   actorObject = ed.spawn_actor_from_class(importlines, nv, rt, transient=False)
// 			   SceneComponent = actorObject.root_component
// 			   SplineComponent = SceneComponent.get_child_component(1)
// 			   SplineComponent.clear_spline_points()
// 	}else
// 	{
// 		SplineComponent.add_spline_point_at_index(nv, pi, unreal.SplineCoordinateSpace.WORLD)
// 	   SplineComponent.set_spline_point_type(pi, SplinePointType, update_spline=True)

//UObject* BPImport = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/UnrealMapboxBridge/Blueprints/ImportLines.ImportLines")));
//UObject* SpawnA = GEditor->GetEditorWorldContext().World()->SpawnActor<BPImport>;

//ATribesmenWeapon* Spawner = GetWorld()->SpawnActor<ATribesmenWeapon>(WeaponSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);
//UBlueprint* importlines;

//importlines = UEditorAssetLibrary().LoadBlueprintClass('/Game/ImportLines');


// UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
// SpawnedActor = World->SpawnActorDeferred<AGameplayAbilityTargetActor>(Class, FVector::ZeroVector, FRotator::ZeroRotator, NULL, NULL, true);
// SensorActor = SpawnBP<AActor>(GetWorld(), MyItemBlueprint, this->GetActorLocation(), this->GetActorRotation());


// UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/UnrealMapboxBridge/Blueprints/ImportLines.ImportLines")));
//
// UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
// if (!SpawnActor)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
// 	return;
// }
//
// UClass* SpawnClass = SpawnActor->StaticClass();
// if (SpawnClass == NULL)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
// 	return;
// }

// UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/DEXIED/Foliage/Tree/BP_TreeDestroyed_Style_1.BP_TreeDestroyed_Style_1")));
//
// UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
// if (!SpawnActor)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
// 	return;
// }
//
// UClass* SpawnClass = SpawnActor->StaticClass();
// if (SpawnClass == NULL)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
// 	return;
// }
// USceneComponent* SceneComponent;
//AmySphere* mySphere =  GetWorld()->SpawnActor<AmySphere>(MyItemBlueprint::StaticClass(), myLoc, myRot, SpawnInfo);

// ChildSceneComponent = 
//  CreateDefaultSubobject<USceneComponent>
//  ("ChildSceneComponent");

// TSubclassOf<AActor> spawnedClass;
//
// // This string is obtained by right clicking the asset in the content browser and selecting "CopyReference", then pasting in a text file.
// FString spawnedBlueprintReference = TEXT("Blueprint'/Game/FirstPersonCPP/Blueprints/FirstPersonProjectile.FirstPersonProjectile'");
//    
// UObject* loadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *spawnedBlueprintReference);
//    
// UBlueprint* castedBlueprint = Cast<UBlueprint>(someObject);
//    
// if (castedBlueprint && castedBlueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
// {
// 	// Don't forget the asterisk
// 	spawnedClass = *castedBlueprint->GeneratedClass;
// }


// UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/DEXIED/Foliage/Tree/BP_TreeDestroyed_Style_1.BP_TreeDestroyed_Style_1")));
//
// UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
// if (!SpawnActor)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
// 	return;
// }
//
// UClass* SpawnClass = SpawnActor->StaticClass();
// if (SpawnClass == NULL)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
// 	return;
// }
//
// UWorld* World = GetWorld();
// FActorSpawnParameters SpawnParams;
// SpawnParams.Owner = this;
// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

//
// FString spawnedBlueprintReference = TEXT("Blueprint'/UnrealMapboxBridge/Blueprints/ImportLines.ImportLines'");
// //    
// UObject* loadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *spawnedBlueprintReference);
