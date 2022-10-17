// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAPIComponent.h"
#include "Json.h"
#include "http.h"
#include "HttpModule.h"

DEFINE_LOG_CATEGORY_STATIC(HTTP_REQUEST_RESPONSE, Log, Log)

void UHTTPAPIComponent::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< Updated upstream
	SignUpRequest("glebrinner@gmail.com", "1122");
=======
	SignInRequest("glebrinner@gmail.com", "1122");
>>>>>>> Stashed changes
}

void UHTTPAPIComponent::SignUpRequest(FString Email, FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

<<<<<<< Updated upstream
	TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/signup");
	Request->SetVerb("GET");
=======
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);

	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Request : %s"), *RequestJsonObject->GetStringField("email"))

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/signup");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
>>>>>>> Stashed changes
	Request->ProcessRequest();
}

void UHTTPAPIComponent::SignInRequest(FString Email, FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);

<<<<<<< Updated upstream
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/login/");
=======
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Request : %s"), *RequestJsonObject->GetStringField("email"))

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceived);
	Request->SetURL("https://m2e-backend-auth.production.bc.gotbitgames.co/auth/login");
>>>>>>> Stashed changes
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UHTTPAPIComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
<<<<<<< Updated upstream
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
=======
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("RESPONSE MESSAGE /n%s"), *Response->GetContentAsString())
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s /nmessage : %s"), *ResponseObject->GetStringField("success"),*ResponseObject->GetStringField("message"))
>>>>>>> Stashed changes
}

UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
