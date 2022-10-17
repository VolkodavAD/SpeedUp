// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interfaces/IHttpRequest.h"
#include "HTTPAPIComponent.generated.h"

class UActorComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPEEDUP_API UHTTPAPIComponent : public UActorComponent
{
	GENERATED_BODY()

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);

public:
	UHTTPAPIComponent();

	UPROPERTY(BlueprintReadOnly)
	FString LoginResult;
	
	UPROPERTY(BlueprintReadOnly)
	FString Message;
	
	UPROPERTY(BlueprintReadOnly)
	FString Data;

	UPROPERTY(BlueprintReadOnly)
	FString ClientEmail;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SignUpRequest(const FString Email, const FString Password);

	UFUNCTION(BlueprintCallable)
	void SignInRequest(const FString Email, const FString Password);
};
