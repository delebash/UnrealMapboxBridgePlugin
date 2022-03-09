// Fill out your copyright notice in the Description page of Project Settings.


#include "GeoJsonStructGeneratorComponent.h"

#include "JsonUtilities.h"

#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include <vector>
#include <string>
#include  <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

// // Sets default values for this component's properties
UGeoJsonStructGeneratorComponent::UGeoJsonStructGeneratorComponent()
{
}


// void tokenize(string &str, char delim, vector<string> &out)
// {
// 	size_t start;
// 	size_t end = 0;
//
// 	while ((start = str.find_first_not_of(delim, end)) != string::npos)
// 	{
// 		end = str.find(delim, start);
// 		out.push_back(str.substr(start, end - start));
// 	}
// }

void UGeoJsonStructGeneratorComponent::OpenMyFileDialog(const FString& DialogTitle, const FString& DefaultPath,
                                                        const FString& FileTypes, TArray<FString>& OutFileNames)
{
	if (GEngine)

	{
		//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		if (DesktopPlatform)
		{
			//Opening the file picker!
			uint32 SelectionFlag = 0;
			//A value of 0 represents single file selection while a value of 1 represents multiple file selection
			DesktopPlatform->OpenFileDialog(NULL, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag,
			                                OutFileNames);
		}
	}
}


FString UGeoJsonStructGeneratorComponent::ParseJsonToString(FString FilePath, FString FileName)
{

	FilePath += + "\\" + FileName;
	FString JsonString; //Json converted to FString
	FFileHelper::LoadFileToString(JsonString, *FilePath);
	return JsonString;
	//std::string MyStdString(TCHAR_TO_UTF8(*JsonString));
}
//
// void UGeoJsonStructGeneratorComponent::ConvertLongLatToXY(FJsonValueArray arry)
// {
// 	auto test = arry;
//
// 	return test;
// }


// void from_json(const nlohmann::json& object, Inner& i)
// {
// 	// j.at("Name").get_to(i.Name);
// 	// j.at("Value").get_to(i.Value);
//
// 	if (object.contains("type"))
// 	{
// 		object.at("type").get_to(i.Value);
// 	}
// 	object.at("geometry")["type"].get_to(i.Value);
// }


void UGeoJsonStructGeneratorComponent::ParseJson(const FString& File, TArray<FGeoJsonStruct>& GeoJsonStructs)
{
	// json j;
	// ifstream ifs(*File);
	// if (!ifs.is_open())
	// {
	// 	//return false;;
	// }
	// ifs >> j;
	// ifs.close();


	// // iterate the array
	// for (json::iterator it = j.begin(); it != j.end(); ++it) {
	// 	std::cout << *it << '\n';
	// }
	//
	// // range-based for
	// for (auto& element : j) {
	// 	std::cout << element << '\n';
	// }

	
// 	for (auto& elm : j.items())
// 	{
// 		nlohmann::json object = elm.value();
//
// 		string type;
// 		int32 id;
// 		string sourceLayer;
// 		string source;
//
// 		string Geotype = object.at("geometry")["type"];
//
// 		nlohmann::json GeoArrycoordinates = object.at("geometry")["coordinates"];
//
// 		if (object.contains("type"))
// 		{
// 			type = object.at("type");
// 		}
// 		nlohmann::json Objproperties = object.at("properties");
//
// 		if (object.contains("id"))
// 		{
// 			id = object.at("id");
// 		}
//
// 		nlohmann::json Objlayer = object.at("layer");
//
// 		if (object.contains("sourceLayer"))
// 		{
// 			sourceLayer = object.at("sourceLayer");
// 		}
//
// 		if (object.contains("source"))
// 		{
// 			source = object.at("source");
// 		}
//
// 		nlohmann::json Objstate = object.at("state");
//
//
// 		if (Geotype == "LineString")
// 		{
// 			// JsonCoordinatesArray = Coordinates[1]->AsArray();
// 		}
//
// 		
//
//
//
//
//
//
// 		// FString Geotype(SGeotype. c_str());
// 		// FString type(Stype.c_str());
// 		// 
// 		// FGeoJsonStruct GeoJsonStruct = FGeoJsonStruct::BuildGeoJsonStruct(
// 		// 	Geotype, type
// 		// );
// 		//
// 		// GeoJsonStructs.Push(GeoJsonStruct);
// 		// from_json();
// 		// FString Geotype(SGeotype.c_str());
// 		// FString type(Stype.c_str());
// 		//
// 		//
// 		// FGeoJsonStruct GeoJsonStruct = FGeoJsonStruct::BuildGeoJsonStruct(
// 		// 	Geotype, type
// 		// );
// 		//
// 		// GeoJsonStructs.Push(GeoJsonStruct);
// 		//std::cout << id << std::endl;
// 		// GLog->Log("multiline done");
// 	}
}


//
// void UGeoJsonStructGeneratorComponent::GenerateStructsFromJson(const FString& File,
//                                                                TArray<FGeoJsonStruct>& GeoJsonStructs)
// {
// 	FString JsonString; //Json converted to FString
// 	FFileHelper::LoadFileToString(JsonString, *File);;
//
// 	// char* path = TCHAR_TO_ANSI(*File);
// 	//
// 	// string s=path;
// 	// char d='-';
// 	// vector<string> a;
// 	// tokenize(s,d,a);
// 	// string & zoom = a.at(1);
// 	// string & resolution = a.at(4);
// 	// GLog->Log(zoom.c_str());
// 	// GLog->Log(resolution.c_str());
//
//
// 	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*JsonString);
// 	TArray<TSharedPtr<FJsonValue>> RawJsonValueArray;
// 	bool success = FJsonSerializer::Deserialize(JsonReader, RawJsonValueArray);
//
//
// 	if (success)
// 	{
// 		for (int32 Index = 0; Index < RawJsonValueArray.Num(); Index++)
// 		{
// 			TSharedPtr<FJsonObject>* JsonObject = new TSharedPtr<FJsonObject>(RawJsonValueArray[Index]->AsObject());
// 			FJsonObject* GeoJsonObject = JsonObject->Get();
// 			FString GeometryType;
// 			FString Type;
// 			TArray<TSharedPtr<FJsonValue>> JsonCoordinatesArray;
// 			// FVector GeometryLongLat;
//
// 			//	TSharedPtr<FJsonValue> GeoJsonValue = RawJsonValueArray[Index];
// 			//	TSharedPtr<FJsonObject> GeoJsonObject = GeoJsonValue->AsObject();
//
// 			if (GeoJsonObject->HasField("geometry"))
// 			{
// 				TSharedPtr<FJsonObject> geometry = GeoJsonObject->GetObjectField("geometry");
//
// 				if (GeoJsonObject->HasField("type"))
// 				{
// 					Type = GeoJsonObject->GetStringField("type");
// 				}
// 				if (geometry->HasField("type"))
// 				{
// 					GeometryType = geometry->GetStringField("type");
// 				}
//
//
// 				TArray<TSharedPtr<FJsonValue>> Coordinates = geometry->GetArrayField("coordinates");
// 				if (GeometryType == "MultiLineString")
// 				{
// 					JsonCoordinatesArray = Coordinates[0]->AsArray();
// 				}
// 				if (GeometryType == "LineString")
// 				{
// 					JsonCoordinatesArray = Coordinates;
// 				}
//
// 				if (GeometryType == "LineString")
// 				{
// 					JsonCoordinatesArray = Coordinates[1]->AsArray();
// 				}
// 				double Long;
// 				double Lat;
// 				TArray<FVector> GeometryCoordinates;
//
// 				for (int32 i = 0; i < JsonCoordinatesArray.Num(); i++)
// 				{
// 					TArray<TSharedPtr<FJsonValue>> JsonLongLat = JsonCoordinatesArray[i]->AsArray();
// 					Long = JsonLongLat[0]->AsNumber();
// 					Lat = JsonLongLat[1]->AsNumber();
//
// 					FVector LonLatCoordinates;
//
// 					LonLatCoordinates.X = Long;
// 					LonLatCoordinates.Y = Lat;
//
// 					GeometryCoordinates.Push(LonLatCoordinates);
//
// 					FGeoJsonStruct GeoJsonStruct = FGeoJsonStruct::BuildGeoJsonStruct(
// 						GeometryType, Type, GeometryCoordinates
// 					);
//
// 					GeoJsonStructs.Push(GeoJsonStruct);
//
//
// 					// 
// 					// if (GeoJsonObject->HasField("properties"))
// 					// {
// 					// 	TSharedPtr<FJsonObject> properties = GeoJsonObject->GetObjectField("properties");;
// 					// }
// 					// if (GeoJsonObject->HasField("layer"))
// 					// {
// 					// 	TSharedPtr<FJsonObject> layer = GeoJsonObject->GetObjectField("layer");
// 					// }
// 					// if (GeoJsonObject->HasField("source"))
// 					// {
// 					// 	FString source = GeoJsonObject->GetStringField("source");
// 					// }
// 					// if (GeoJsonObject->HasField("id"))
// 					// {
// 					// 	FString source = GeoJsonObject->GetStringField("id");
// 					// }
// 					// if (GeoJsonObject->HasField("state"))
// 					// {
// 					// 	TSharedPtr<FJsonObject> state = GeoJsonObject->GetObjectField("state");
// 					// }
// 				}
// 			}
// 		}
// 	}
// }
