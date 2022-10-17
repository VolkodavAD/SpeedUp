// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveFile.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDUP_API USaveFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Rinner", meta=(Keywords = "SaveData"))
	static bool SaveDataText(FString SaveDirectory, FString FileName, TArray<FString> SaveText,
		bool AllowOverWriting);

	UFUNCTION(BlueprintCallable, Category="Rinner", meta=(Keywords = "LoadData"))
	static FString LoadFileToString(FString FileName);

	UFUNCTION(BlueprintCallable, Category="Rinner", meta=(Keywords = "LoadData"))
	static TArray<FString> LoadFileToStringArray(FString FileName);
};
