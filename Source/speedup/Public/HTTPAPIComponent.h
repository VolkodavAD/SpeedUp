// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interfaces/IHttpRequest.h"
#include "HTTPAPIComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FResponseDelegat);

class UActorComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPEEDUP_API UHTTPAPIComponent : public UActorComponent
{
	GENERATED_BODY()

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);

public:
	UHTTPAPIComponent();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SignUpRequest(FString Email, FString Password);

	UFUNCTION(BlueprintCallable)
	void SignInRequest(FString Email, FString Password);
};
