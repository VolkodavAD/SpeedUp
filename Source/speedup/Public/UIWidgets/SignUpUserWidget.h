// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
};
