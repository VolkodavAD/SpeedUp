// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveFile.h"

bool USaveFile::SaveDataText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverWriting)
{
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	if(!AllowOverWriting)
	{
		if(FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}

	FString FinalString = "";
	for (FString& Each : SaveText)
	{
		FinalString += Each;
		FinalString += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);
}

FString USaveFile::LoadFileToString(FString FileName)
{
	const FString DirectoryName = FPaths::GameUserDeveloperFolderName();
	FString Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if(File.CreateDirectory(*DirectoryName))
	{
		FString UserFile = DirectoryName + "/" + FileName;
		FFileHelper::LoadFileToString(Result, *UserFile);
	}

	return Result;
}

TArray<FString> USaveFile::LoadFileToStringArray(FString FileName)
{
	const FString DirectoryName = FPaths::GameUserDeveloperFolderName();
	TArray<FString> Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if(File.CreateDirectory(*DirectoryName))
	{
		FString UserFile = DirectoryName + "/" + FileName;
		FFileHelper::LoadFileToStringArray(Result, *UserFile);
	}

	return Result;
}
