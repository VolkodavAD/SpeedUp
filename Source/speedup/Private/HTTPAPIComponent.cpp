// Fill out your copyright notice in the Description page of Project Settings.

#include "HTTPAPIComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "..\Public\HTTPAPIComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HTTP_REQUEST_RESPONSE, Log, Log)

void UHTTPAPIComponent::BeginPlay()
{
	Super::BeginPlay();

	bSuccess = false;
}

void UHTTPAPIComponent::SignUpRequest(const FString Email, const FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);
	//токен
	//RequestJsonObject->SetStringField("token", Password);
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSignUP);
	Request->SetURL(SignUPURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
	
	ClientEmail = Email;
}

void UHTTPAPIComponent::SignInRequest(const FString Email, const FString Password)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSignIN);
	Request->SetURL(SignINURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
	
	ClientEmail = Email;
}

void UHTTPAPIComponent::LogoutRequest(const FString DataToken)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("data", DataToken);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedLogOut);
	Request->SetURL(LogOutURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UHTTPAPIComponent::CodeRequestFromServer(const FString DataToken)
{
	const FHttpRequestRef RequestSendCode = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("data", DataToken);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	FString BearerT = "Bearer_";
	RequestSendCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSendCode);
	RequestSendCode->SetURL(SendCodeURL);
	RequestSendCode->SetVerb("POST");
	RequestSendCode->SetHeader("Content-Type", "application/json");
	RequestSendCode->AppendToHeader("Authorization", BearerT.Append(DataToken));
	RequestSendCode->SetContentAsString(RequestBody);
	RequestSendCode->ProcessRequest();

}

void UHTTPAPIComponent::Verify(const FString CodeFromMail, const FString TokenData)
{
	const FHttpRequestRef VerifyCode = FHttpModule::Get().CreateRequest();

	//FString CodeFromMail = "123456";
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("code", CodeFromMail);
	//токен
	//RequestJsonObject->SetStringField("token", Password);
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	FString BearerT = "Bearer_";
	//TokenData = "eyJhbGciOiJFZERTQSIsInR5cCI6IkpXVCJ9.eyJleHAiOjE2NjUyMDU0OTQsImlhdCI6MTY2NTA5NzQ5NCwiaXNzIjoia2trIiwic3ViIjoianZvZWV2IiwibmFtZSI6ImhhaGFsb2w5MTVAZ21haWwuY29tIiwiZ2xvYmFsIjp0cnVlLCJhYmlsaXRpZXMiOnsiZW1haWwtY29kZSI6WyJwZXJzb24uaGFoYWxvbDkxNUBnbWFpbC5jb20iXX19.6KQyx1lQ5kQrS33Y0JXPp1NgqElEZ1vdyTdSDAExFasF6Gp5fc7q-yqEmn2_NyUK47guFZYZOjR2_dUDLKmeAA";
	VerifyCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedVerefi);
	VerifyCode->SetURL(VerifiURL);
	VerifyCode->SetVerb("POST");
	VerifyCode->SetHeader("Content-Type", "application/json");
	VerifyCode->AppendToHeader("Authorization", BearerT.Append(TokenData));
	VerifyCode->SetContentAsString(RequestBody);
	VerifyCode->ProcessRequest();
}

void UHTTPAPIComponent::OnResponseReceivedSignIN(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedLogOut(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedSendCode(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);
	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	Data = ResponseObject->GetStringField("data");

	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
		UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
		UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
		UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedSignUP(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	Data = ResponseObject->GetStringField("data");
	
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedVerefi(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	Data = ResponseObject->GetStringField("data");

	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}