// Fill out your copyright notice in the Description page of Project Settings.

#include "HTTPAPIComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "SpeedUpGameInstance.h"
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
	//RequestJsonObject->SetStringField("data", ClientTocken);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	FString BearerT = "Bearer ";
	RequestSendCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSendCode);
	RequestSendCode->SetURL(SendCodeURL);
	RequestSendCode->SetVerb("POST");
	RequestSendCode->SetHeader("Content-Type", "application/json");
	RequestSendCode->AppendToHeader("Authorization", BearerT.Append(DataToken));
	//RequestSendCode->AppendToHeader("Authorization", DataToken);
	RequestSendCode->SetContentAsString(RequestBody);
	RequestSendCode->ProcessRequest();
}

void UHTTPAPIComponent::Verify(const FString CodeFromMail, const FString TokenData)
{
	const FHttpRequestRef VerifyCode = FHttpModule::Get().CreateRequest();

	//FString CodeFromMail = "123456";
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("code", CodeFromMail);
	
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	FString BearerT = "Bearer ";
	VerifyCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedVerefi);
	VerifyCode->SetURL(VerifiURL);
	VerifyCode->SetVerb("POST");
	VerifyCode->SetHeader("Content-Type", "application/json");
	VerifyCode->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	VerifyCode->SetContentAsString(RequestBody);
	VerifyCode->ProcessRequest();
}

void UHTTPAPIComponent::Profile(const FString TokenData)
{
	const FHttpRequestRef ProfileCode = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	//RequestJsonObject->SetStringField("code", CodeFromMail);
	/*
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	*/
	FString BearerT = "Bearer ";
	ProfileCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedProfile);
	ProfileCode->SetURL(ProfileURL);
	ProfileCode->SetVerb("GET");
	ProfileCode->SetHeader("Content-Type", "application/json");
	ProfileCode->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	//ProfileCode->SetContentAsString(RequestBody);
	ProfileCode->ProcessRequest();
}

void UHTTPAPIComponent::OnResponseReceivedSignIN(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	else
	{
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		ClientTocken = ResponseObject->GetStringField("data");
	}
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"));
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"));
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"));
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString());
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

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	else
	{
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		//Data = ResponseObject->GetStringField("data");
	}
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedSignUP(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	else
	{
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		Data = ResponseObject->GetStringField("data");
	}
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

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	else
	{
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		Data = ResponseObject->GetStringField("data");
		ClientTocken = ResponseObject->GetStringField("data");
	}
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedProfile(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);
	
	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	else
	{
		UWorld* world = GetWorld();
		if (world)
		{
			USpeedUpGameInstance* gameInstance = Cast<USpeedUpGameInstance>(world->GetGameInstance());

			if (gameInstance)
			{
				//gameInstance->GetSaveManager()->FlushCachedSaveData();
				//UGameplayStatics::OpenLevel(world, FName(*world->GetName()));


				//UGameplayStatics::GetGameInstance()

				//TSharedPtr<FJsonObject> ObjectResult;

				Message = ResponseObject->GetStringField("message");
				bSuccess = ResponseObject->GetBoolField("success");
				//Data = ResponseObject->GetStringField("data");

				TSharedPtr<FJsonObject> nested = ResponseObject->GetObjectField("data");
				FString Profile_Name = nested->GetStringField("email");
				int Profile_id = nested->GetIntegerField("id");
				bool Profile_email_confirmed = nested->GetBoolField("email_confirmed");


				TSharedPtr<FJsonObject> balances = nested->GetObjectField("balances");
				FString balances_dks_wallet = balances->GetStringField("dks_wallet");
				int balances_dks_balance = balances->GetIntegerField("dks_balance");
				int balances_internal_balance = balances->GetIntegerField("internal_balance");

				TSharedPtr<FJsonObject> energy = nested->GetObjectField("energy");
				int user_id = energy->GetIntegerField("energy");
				uint8 capacity = energy->GetIntegerField("capacity"); // Byte
				uint8 spend_part = energy->GetIntegerField("spend_part");  // Byte
				FString updated_at = energy->GetStringField("updated_at");
				bool active = energy->GetBoolField("active");

				//ObjectData = ResponseObject->GetObjectField("data");


				gameInstance->UserInfo.email = Profile_Name;
				gameInstance->UserInfo.email_confirmed = Profile_email_confirmed;
				gameInstance->UserInfo.id = Profile_id;

				gameInstance->UserInfo.Balance.dks_wallet = balances_dks_wallet;
				gameInstance->UserInfo.Balance.dks_balance = balances_dks_balance;
				gameInstance->UserInfo.Balance.internal_balance = balances_internal_balance;

				gameInstance->UserInfo.Energy.capacity = capacity;
				gameInstance->UserInfo.Energy.spend_part = spend_part;
				gameInstance->UserInfo.Energy.updated_at = updated_at;
				gameInstance->UserInfo.Energy.active = active;
			}
		}
	}

	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}