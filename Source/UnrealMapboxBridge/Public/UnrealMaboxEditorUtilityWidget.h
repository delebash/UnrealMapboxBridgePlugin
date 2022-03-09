// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "EditorUtilityWidget.h"
// #include "JsonUtilities.h"
// #include "UnrealMaboxEditorUtilityWidget.generated.h"
//
// /**
//  * 
//  */
// UCLASS(Blueprintable)
// class UNREALMAPBOXBRIDGE_API UMapboxEditorUtilityWidget : public UEditorUtilityWidget
// {
// 	GENERATED_BODY()
// public:
// 	UMapboxEditorUtilityWidget();
// 	~UMapboxEditorUtilityWidget();
//
// 	UFUNCTION(BlueprintCallable, Category = "UnrealMapbox")
// 	void OpenMyFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);
//
// 	// UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Class",
// 	//  CompactNodeTitle = "New", Keywords = "new create blueprint"), Category = Game)
//
// 	/*Prints the data of the given file*/
// 	UFUNCTION(BlueprintCallable, Category = "UnrealMapbox")
// 	static bool ParseGeoJson(const FString& File);
// 	
// };
