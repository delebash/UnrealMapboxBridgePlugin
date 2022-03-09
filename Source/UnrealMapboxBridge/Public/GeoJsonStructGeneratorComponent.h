// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "GeoJsonStruct.h"
#include "GeoJsonStructGeneratorComponent.generated.h"


UCLASS(Blueprintable)
class UNREALMAPBOXBRIDGE_API UGeoJsonStructGeneratorComponent : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UGeoJsonStructGeneratorComponent();

	UFUNCTION(BlueprintCallable, Category = "UnrealMapbox")
	void OpenMyFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes,
	                      TArray<FString>& OutFileNames);


	UFUNCTION(BlueprintCallable, Category = "UnrealMapbox")
	static FString ParseJsonToString(FString FilePath, FString FileName);
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UnrealMapbox")
	// FString health;
	// UFUNCTION(BlueprintCallable, Category = "UnrealMapbox")
	//  void ConvertLongLatToXY(FJsonValueArray arry);

	
		void ParseJson(const FString& File, TArray<FGeoJsonStruct>& GeoJsonStructs);


	//	void GenerateStructsFromJson(const FString& File, TArray<FGeoJsonStruct> &GeoJsonStructs);


private:
	// FString JsonFullPath(FString Path);

	//FVector ParseAsVector(TSharedPtr<FJsonObject> json, FString KeyName);

	//FRotator ParseAsRotator(TSharedPtr<FJsonObject> json, FString KeyName);
};
