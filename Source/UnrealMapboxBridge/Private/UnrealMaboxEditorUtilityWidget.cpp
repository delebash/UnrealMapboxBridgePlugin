// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "UnrealMaboxEditorUtilityWidget.h"
//
// #include <string>
//
// #include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
// #include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
// #include "JsonUtilities.h"
//
//
// UMapboxEditorUtilityWidget::UMapboxEditorUtilityWidget()
// {
// }
//
// UMapboxEditorUtilityWidget::~UMapboxEditorUtilityWidget()
// {
// }
//
// void UMapboxEditorUtilityWidget::OpenMyFileDialog(const FString& DialogTitle, const FString& DefaultPath,
//                                                   const FString& FileTypes, TArray<FString>& OutFileNames)
// {
// 	if (GEngine)
//
// 	{
// 		//void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
// 		IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
// 		if (DesktopPlatform)
// 		{
// 			//Opening the file picker!
// 			uint32 SelectionFlag = 0;
// 			//A value of 0 represents single file selection while a value of 1 represents multiple file selection
// 			DesktopPlatform->OpenFileDialog(NULL, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag,
// 			                                OutFileNames);
// 		}
// 	}
// }
//
// bool UMapboxEditorUtilityWidget::ParseGeoJson(const FString& File)
// {
// 	FString JsonString; //Json converted to FString
// 	FFileHelper::LoadFileToString(JsonString, *File);
// 	TArray<TSharedPtr<FJsonValue>> RawJsonValueArray;
// 	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonString);
// 	bool success = FJsonSerializer::Deserialize(Reader, RawJsonValueArray);
//
//
// 	if (success)
// 	{
// 		GLog->Log("deserialize success");
//
// 		for (int32 index = 0; index < RawJsonValueArray.Num(); index++)
// 		{
// 			TSharedPtr<FJsonObject>* JsonObject = new TSharedPtr<FJsonObject>(RawJsonValueArray[index]->AsObject());
// 			FJsonObject* GeoJsonObject = JsonObject->Get();
//
// 			if (GeoJsonObject->HasField("geometry"))
// 			{
// 				TSharedPtr<FJsonObject> geometry = GeoJsonObject->GetObjectField("geometry");
// 				FString Geotype = geometry->GetStringField("type");
// 				TArray<TSharedPtr<FJsonValue>> coordinates = geometry->GetArrayField("coordinates");
// 				TArray<TSharedPtr<FJsonValue>> ptsArray = coordinates[0]->AsArray();
//
// 				for (int32 i = 0; i < ptsArray.Num(); i++)
// 				{
// 					TArray<TSharedPtr<FJsonValue>> pts = ptsArray[i]->AsArray();
// 					FJsonValueNumber pt1 = pts[0]->AsNumber();
// 					FJsonValueNumber pt2 = pts[1]->AsNumber();
// 					GLog->Log("test");
// 				}
// 			}
// 			if (GeoJsonObject->HasField("type"))
// 			{
// 				FString type = GeoJsonObject->GetStringField("type");
// 			}
// 			if (GeoJsonObject->HasField("properties"))
// 			{
// 				TSharedPtr<FJsonObject> properties = GeoJsonObject->GetObjectField("properties");;
// 			}
// 			if (GeoJsonObject->HasField("layer"))
// 			{
// 				TSharedPtr<FJsonObject> layer = GeoJsonObject->GetObjectField("layer");
// 			}
// 			if (GeoJsonObject->HasField("source"))
// 			{
// 				FString source = GeoJsonObject->GetStringField("source");
// 			}
// 			if (GeoJsonObject->HasField("id"))
// 			{
// 				FString source = GeoJsonObject->GetStringField("id");
// 			}
// 			if (GeoJsonObject->HasField("state"))
// 			{
// 				TSharedPtr<FJsonObject> state = GeoJsonObject->GetObjectField("state");
// 			}
// 		}
// 	}
// 	return true;
// }
//
//
//
//
//
// //
// // // TArray<FCharacterInfo> data;
// // FJsonObjectConverter::JsonArrayStringToUStruct(JsonString, &data, 0, 0);
// // FPerson PersonJSON;
// // if (FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &PersonJSON, 0, 0))
// // {
// // 	UE_LOG(LogTemp, Warning, TEXT("CONVERTED"));
// // 	UE_LOG(LogTemp, Warning, TEXT("Name: %s Age: %d Occupation: %s"), *PersonJSON.Name, 
// // 		PersonJSON.Age, *PersonJSON.Occupation);
// // }
//
//
// // TArray<TSharedPtr<FJsonValue>> RawJsonValueArray;
// // TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*JsonString);
// //bool success = FJsonSerializer::Deserialize(Reader, RawJsonValueArray);
//
// // if (success)
// // {
// //
// //
// // 	TArray<FMyItem> data;
// // 	FJsonObjectConverter::JsonArrayToUStruct(arrayDeserialized, &data, 0, 0);
