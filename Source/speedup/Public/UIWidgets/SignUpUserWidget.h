// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "SignUpUserWidget.generated.h"

class FHttpModule;
class IHttpRequest;

USTRUCT()
struct FData
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ID{-1};
	
	UPROPERTY()
	FString Name{};
};

UCLASS()
class SPEEDUP_API USignUpUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void MakeRequest();

	void OnPostReceivedResponse(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) const
	{
		//Если запрос успешен и ответ валиден.
		if(bWasSuccessful && Response.Get())
		{
			FData Data;
			//Объект сразу закастится к типу FData и будет помещен в out параметр Data. 
			FJsonObjectConverter::JsonObjectStringToUStruct<FData>(Response->GetContentAsString(),&Data);
			Data.ID;//Теперь можно использовать эти данные.
			Data.Name;
		}
	}
	//Таким же образом будет выглядеть преобразование из структуры в строку:
	FString GetContent(const FData& Object) const
	{
		FString ReturnString;
		FJsonObjectConverter::UStructToJsonObjectString<const FData>(Object,ReturnString);
		return ReturnString;
	}
};
