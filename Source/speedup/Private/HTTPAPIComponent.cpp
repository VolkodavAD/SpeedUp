// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAPIComponent.h"
#include "Json.h"
#include "http.h"
#include "HttpModule.h"

DEFINE_LOG_CATEGORY_STATIC(HTTP_REQUEST_RESPONSE, Log, Log)

void UHTTPAPIComponent::BeginPlay()
{
	Super::BeginPlay();
	SignUpRequest("glebrinner@gmail.com", "1122");
}

void UHTTPAPIComponent::SignUpRequest(FString Email, FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/signup");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UHTTPAPIComponent::SignInRequest(FString Email, FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/login/");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UHTTPAPIComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
