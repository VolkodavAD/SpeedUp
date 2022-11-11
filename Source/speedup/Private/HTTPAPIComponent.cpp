// Fill out your copyright notice in the Description page of Project Settings.

#include "HTTPAPIComponent.h"
#include "HttpModule.h"
#include "Items/Item.h"
#include "widgets/BaseWalletWidget.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "..\Public\SpeedUpGameInstance.h" 
#include "..\speedupGameModeBase.h"
#include "..\Public\HTTPAPIComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HTTP_REQUEST_RESPONSE, Log, Log)


void UHTTPAPIComponent::BeginPlay()
{
	Super::BeginPlay();
	bSuccess = false;
}

void UHTTPAPIComponent::InitComponent()
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	ClientEmail = SpeedUpGI->UserInfo.email;
	ClientTocken = SpeedUpGI->UserInfo.UserToken;
}

void UHTTPAPIComponent::SignUpRequest(const FString Email, const FString Password)
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());

	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("email", Email);
	RequestJsonObject->SetStringField("password", Password);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter =TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);	
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSignUP);
	Request->SetURL(SignUPURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();

	SpeedUpGI->UserInfo.email = Email;
	ClientEmail = Email;
}

void UHTTPAPIComponent::SignInRequest(const FString Email, const FString Password)
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	SpeedUpGI->UserInfo.email = Email;

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

void UHTTPAPIComponent::ChangePassword(const FString OldPassword, const FString NewPassword, const FString TokenData)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetStringField("old_password", OldPassword);
	RequestJsonObject->SetStringField("new_password", NewPassword);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	FString BearerT = "Bearer ";
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedChangePassword);
	Request->SetURL(ChangePasswordURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UHTTPAPIComponent::RepairPassword(const FString NewPassword, const FString RecoveryCode, const FString Email)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	
	RequestJsonObject->SetStringField("new_password", NewPassword);
	RequestJsonObject->SetStringField("code", RecoveryCode);
	RequestJsonObject->SetStringField("email", Email);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedRepairPassword);
	Request->SetURL(PasswordRepairURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UHTTPAPIComponent::SendRecoveryCode(const FString Email)
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();

	RequestJsonObject->SetStringField("email", Email);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedRecoveryCode);
	Request->SetURL(SendRecoveryCodeURL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();

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


	FString BearerT = "Bearer ";
	FString RequestBody;

	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	RequestSendCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSendCode);
	RequestSendCode->SetURL(SendCodeURL);
	RequestSendCode->SetVerb("POST");
	RequestSendCode->SetHeader("Content-Type", "application/json");
	RequestSendCode->AppendToHeader("Authorization", BearerT.Append(DataToken));
	//RequestSendCode->AppendToHeader("Authorization", DataToken);
	RequestSendCode->SetContentAsString(RequestBody);
	RequestSendCode->ProcessRequest();
}

void UHTTPAPIComponent::NFTreceiptRequest(const FString TokenData)
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());

	FString BearerT = "Bearer ";

	const FHttpRequestRef NFTget = FHttpModule::Get().CreateRequest();
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();

	NFTget->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedNFTreceipt);
	NFTget->SetURL(NFTreceiptRequestURL);
	NFTget->SetVerb("GET");
	NFTget->SetHeader("Content-Type", "application/json");
	NFTget->AppendToHeader("Authorization", BearerT.Append(SpeedUpGI->UserInfo.UserToken));	
	NFTget->ProcessRequest();
}

void UHTTPAPIComponent::NFTactivationRequest(const int NFDId)
{
	const FHttpRequestRef RequestActiveNFT = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetNumberField("nft_id", NFDId);
	//токен
	//RequestJsonObject->SetStringField("token", Password);
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

	FString BearerT = "Bearer ";
	RequestActiveNFT->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedActivation);
	RequestActiveNFT->SetURL(NFTActiveRequestURL);
	RequestActiveNFT->SetVerb("POST");
	RequestActiveNFT->SetHeader("Content-Type", "application/json");
	RequestActiveNFT->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	RequestActiveNFT->SetContentAsString(RequestBody);

	ActivationItem = NFDId;
	RequestActiveNFT->ProcessRequest();
}

//{
//"id" :0,
//"user_id" : 0,
//"nft_id" : 0,
//"nft_type" : 0,
//"avg_velocity" : 0.00,
//"avg_distance:0.00"
//}

void UHTTPAPIComponent::NFTdeactivationRequest(const int DeactivePathID, const int DeactivNFDId, const float avg_velocity, const float avg_distance)
{
	USpeedUpGameInstance* GameIst = (USpeedUpGameInstance*)GetWorld()->GetGameInstance();
	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
	UItem* DeactivNFDIdItem = GameMode->GetNFTItemManager()->GetMyItem(DeactivNFDId);

	const FHttpRequestRef RequestActiveNFT = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetNumberField("id", DeactivePathID);
	RequestJsonObject->SetNumberField("user_id", GameIst->UserInfo.id);
	RequestJsonObject->SetNumberField("nft_id", DeactivNFDId);
	RequestJsonObject->SetNumberField("nft_type", (float)DeactivNFDIdItem->GetType());
	RequestJsonObject->SetNumberField("avg_velocity", avg_velocity);
	RequestJsonObject->SetNumberField("avg_distance", avg_distance);

	//токен
	//RequestJsonObject->SetStringField("token", Password);
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

	FString BearerT = "Bearer ";
	RequestActiveNFT->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedUpdate);
	RequestActiveNFT->SetURL(NFTDeactiveRequestURL);
	RequestActiveNFT->SetVerb("POST");
	RequestActiveNFT->SetHeader("Content-Type", "application/json");
	RequestActiveNFT->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	RequestActiveNFT->SetContentAsString(RequestBody);

	RequestActiveNFT->ProcessRequest();
}

void UHTTPAPIComponent::NFTUpdateRequest(const int DeactivePathID, const int DeactivNFDId, const float avg_velocity, const float avg_distance)
{
	USpeedUpGameInstance* GameIst = (USpeedUpGameInstance*)GetWorld()->GetGameInstance();
	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
	UItem* DeactivNFDIdItem = GameMode->GetNFTItemManager()->GetMyItem(DeactivNFDId);

	if (DeactivNFDIdItem)
	{
		const FHttpRequestRef RequestActiveNFT = FHttpModule::Get().CreateRequest();

		const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
		RequestJsonObject->SetNumberField("id", DeactivePathID);
		RequestJsonObject->SetNumberField("user_id", GameIst->UserInfo.id);
		RequestJsonObject->SetNumberField("nft_id", DeactivNFDId);
		RequestJsonObject->SetNumberField("nft_type", (float)DeactivNFDIdItem->GetType());
		RequestJsonObject->SetNumberField("avg_Speed", avg_velocity);
		RequestJsonObject->SetNumberField("avg_distanse", avg_distance);

		//токен
		//RequestJsonObject->SetStringField("token", Password);
		FString RequestBody;
		const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
		FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

		FString BearerT = "Bearer ";
		RequestActiveNFT->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedActivation);
		RequestActiveNFT->SetURL(NFTUpdateRequestURL);
		RequestActiveNFT->SetVerb("POST");
		RequestActiveNFT->SetHeader("Content-Type", "application/json");
		RequestActiveNFT->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
		RequestActiveNFT->SetContentAsString(RequestBody);

		RequestActiveNFT->ProcessRequest();
	}
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
	ProfileCode->AppendToHeader("Authorization", BearerT.Append(TokenData));
	//ProfileCode->SetContentAsString(RequestBody);
	ProfileCode->ProcessRequest();
}

void UHTTPAPIComponent::StatisticRequest(const ItemType StatItemType, const int Period)
{
	const FHttpRequestRef ProfileCode = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetNumberField("nft_type", (float)StatItemType);
	RequestJsonObject->SetNumberField("period", Period);

	FString BearerT = "Bearer ";
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	ProfileCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedPathStatistick);
	ProfileCode->SetURL(StatisticURL);
	ProfileCode->SetVerb("POST");
	ProfileCode->SetHeader("Content-Type", "application/json");
	ProfileCode->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	ProfileCode->SetContentAsString(RequestBody);
	ProfileCode->ProcessRequest();

	//FString RequestBody;
	//const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	//FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	//Request->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedSignUP);
	//Request->SetURL(SignUPURL);
	//Request->SetVerb("POST");
	//Request->SetHeader("Content-Type", "application/json");
	//Request->SetContentAsString(RequestBody);
	//Request->ProcessRequest();
}

void UHTTPAPIComponent::TransactionsRequest(const int Page, const int Limit, const FString TokenData)
{

	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetNumberField("page", Page);
	RequestJsonObject->SetNumberField("limit", Limit);
	FString BearerT = "Bearer ";
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	const FHttpRequestRef TransactionsRequest = FHttpModule::Get().CreateRequest();
	
	TransactionsRequest->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedTransactions);
	TransactionsRequest->SetURL(TransactionsURL);
	TransactionsRequest->SetVerb("POST");
	TransactionsRequest->SetHeader("Content-Type", "application/json");
	TransactionsRequest->AppendToHeader("Authorization", BearerT.Append(SpeedUpGI->UserInfo.UserToken));
	TransactionsRequest->SetContentAsString(RequestBody);
	TransactionsRequest->ProcessRequest();

}

void UHTTPAPIComponent::BuyingSlotRequest(const FString TokenData)
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	const FHttpRequestRef RequestSendCode = FHttpModule::Get().CreateRequest();
	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	
	FString BearerT = "Bearer ";

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);
	RequestSendCode->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedBuyingSlot);
	RequestSendCode->SetURL(SendCodeURL);
	RequestSendCode->SetVerb("POST");
	RequestSendCode->SetHeader("Content-Type", "application/json");
	RequestSendCode->AppendToHeader("Authorization", BearerT.Append(SpeedUpGI->UserInfo.UserToken));
	RequestSendCode->SetContentAsString(RequestBody);
	RequestSendCode->ProcessRequest();
}

void UHTTPAPIComponent::OnResponseReceivedSignIN(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	if (SpeedUpGI)
	{
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
			ErrorID = Response->GetResponseCode();
			bSuccess = ResponseObject->GetBoolField("success");
			Message = ResponseObject->GetStringField("message");
			ClientTocken = ResponseObject->GetStringField("data");
			SpeedUpGI->UserInfo.UserToken = ClientTocken;

		}
	}
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"));
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"));
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"));
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString());
}

void UHTTPAPIComponent::OnResponseReceivedLogOut(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	bSuccess = ResponseObject->GetBoolField("success");
	Message = ResponseObject->GetStringField("message");
	
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
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
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		//Data = ResponseObject->GetStringField("data");
	}
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
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
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		Data = ResponseObject->GetStringField("data");
	}
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedVerefi(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());
	if (SpeedUpGI)
	{
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
			ErrorID = 0;
			ErrorText = "";
			bSuccess = ResponseObject->GetBoolField("success");
			Message = ResponseObject->GetStringField("message");
			Data = ResponseObject->GetStringField("data");
			ClientTocken = ResponseObject->GetStringField("data");
			SpeedUpGI->UserInfo.UserToken = ClientTocken;
		}
	}
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedChangePassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	int Code = Response->GetResponseCode();
	if (Code != 200)
	{
		Message = "Wrong Password";
		return;
	}

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
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		//Message = ResponseObject->GetStringField("message");
		//Data = ResponseObject->GetStringField("data");
	}
}

void UHTTPAPIComponent::OnResponseReceivedProfile(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());

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
		if (SpeedUpGI)
		{
			//gameInstance->GetSaveManager()->FlushCachedSaveData();
			//UGameplayStatics::OpenLevel(world, FName(*world->GetName()));


			//UGameplayStatics::GetGameInstance()

			//TSharedPtr<FJsonObject> ObjectResult;

			ErrorID = Response->GetResponseCode();
			ErrorText = "";
			Message = ResponseObject->GetStringField("message");
			bSuccess = ResponseObject->GetBoolField("success");
			//Data = ResponseObject->GetStringField("data");

			TSharedPtr<FJsonObject> nested = ResponseObject->GetObjectField("data");
			FString Profile_Name = nested->GetStringField("email");
			int Profile_id = nested->GetIntegerField("id");
			bool Profile_email_confirmed = nested->GetBoolField("email_confirmed");
			int Allowed_slots = nested->GetIntegerField("allowed_slots");

			TSharedPtr<FJsonObject> balances = nested->GetObjectField("balances");
			FString balances_dks_wallet = balances->GetStringField("dks_wallet");
			float balances_dks_balance = balances->GetNumberField("dks_balance");
			float balances_internal_balance = balances->GetNumberField("internal_balance");

			//TSharedPtr<FJsonObject> energy = nested->GetObjectField("energy");
			//int user_id = energy->GetIntegerField("energy");
			//uint8 capacity = energy->GetIntegerField("capacity"); // Byte
			//uint8 spend_part = energy->GetIntegerField("spend_part");  // Byte
			//FString updated_at = energy->GetStringField("updated_at");
			//bool active = energy->GetBoolField("active");

			//ObjectData = ResponseObject->GetObjectField("data");

			SpeedUpGI->UserInfo.email = Profile_Name;
			SpeedUpGI->UserInfo.email_confirmed = Profile_email_confirmed;
			SpeedUpGI->UserInfo.id = Profile_id;
			SpeedUpGI->UserInfo.UserToken = ClientTocken;

			SpeedUpGI->UserInfo.Balance.dks_wallet = balances_dks_wallet;
			SpeedUpGI->UserInfo.Balance.dks_balance = balances_dks_balance;
			SpeedUpGI->UserInfo.Balance.internal_balance = balances_internal_balance;

			//SpeedUpGI->UserInfo.Energy.capacity = capacity;
			//SpeedUpGI->UserInfo.Energy.spend_part = spend_part;
			//SpeedUpGI->UserInfo.Energy.updated_at = updated_at;
			//SpeedUpGI->UserInfo.Energy.active = active;
		}
	}

	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
}

void UHTTPAPIComponent::OnResponseReceivedNFTreceipt(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
	if (!GameMode->IsValidLowLevel())
	{
		return;
	}

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
				ErrorID = 0;
				ErrorText = "";
				Message = ResponseObject->GetStringField("message");
				bSuccess = ResponseObject->GetBoolField("success");


				GameMode->GetNFTItemManager()->ClearItemArray();

				TSharedPtr<FJsonObject> NFT = ResponseObject->GetObjectField("data");
				TMap<FString, TSharedPtr<FJsonValue, ESPMode::ThreadSafe>> MapNFT = NFT->Values;

				TArray<TSharedPtr<FJsonValue>> Points = NFT->GetArrayField(TEXT("Sneaker"));
				FBaseItemInfo NFTItem;
				for (int32 i = 0; i < Points.Num(); ++i)
				{
					TSharedPtr<FJsonObject> PointsObject = Points[i]->AsObject();
					NFTItem.ItemID = PointsObject->GetIntegerField("id");
					NFTItem.Type = static_cast<ItemType>(PointsObject->GetIntegerField("type"));
					NFTItem.CollectionID = PointsObject->GetIntegerField("collection_id");
					NFTItem.Minted = PointsObject->GetBoolField("minted");
					NFTItem.ItemImage = PointsObject->GetStringField("image_url");
					NFTItem.ItemLevel = PointsObject->GetIntegerField("level");
					NFTItem.last_trip_id = PointsObject->GetIntegerField("last_trip_id");
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));
					//NFTItem.NextUpdateTime = PointsObject->GetStringField("next_update");
					TSharedPtr<FJsonObject> energy = PointsObject->GetObjectField("energy");
					NFTItem.NextUpdateTime = energy->GetStringField("next_update");
					NFTItem.capacity = energy->GetIntegerField("capacity"); // Byte
					NFTItem.spendPart = energy->GetIntegerField("spend_part");  // Byte
					NFTItem.active = energy->GetBoolField("active");
					UItem* AddedItem = NewObject<UItem>();
					AddedItem->SetItemInfo(NFTItem);
					GameMode->GetNFTItemManager()->AddItem(AddedItem);
				}

				Points = NFT->GetArrayField(TEXT("Car"));

				for (int32 i = 0; i < Points.Num(); ++i)
				{
					TSharedPtr<FJsonObject> PointsObject = Points[i]->AsObject();
					NFTItem.ItemID = PointsObject->GetIntegerField("id");
					NFTItem.Type = static_cast<ItemType>(PointsObject->GetIntegerField("type"));
					NFTItem.CollectionID = PointsObject->GetIntegerField("collection_id");
					NFTItem.Minted = PointsObject->GetBoolField("minted");
					NFTItem.ItemImage = PointsObject->GetStringField("image_url");
					NFTItem.ItemLevel = PointsObject->GetIntegerField("level");
					NFTItem.last_trip_id = PointsObject->GetIntegerField("last_trip_id");
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));

					TSharedPtr<FJsonObject> energy = PointsObject->GetObjectField("energy");
					NFTItem.capacity = energy->GetIntegerField("capacity"); // Byte
					NFTItem.spendPart = energy->GetIntegerField("spend_part");  // Byte
					NFTItem.active = energy->GetBoolField("active");

					UItem* AddedItem = NewObject<UItem>();
					AddedItem->SetItemInfo(NFTItem);
					GameMode->GetNFTItemManager()->AddItem(AddedItem);
				}

				Points = NFT->GetArrayField(TEXT("Plane"));

				for (int32 i = 0; i < Points.Num(); ++i)
				{
					TSharedPtr<FJsonObject> PointsObject = Points[i]->AsObject();
					NFTItem.ItemID = PointsObject->GetIntegerField("id");
					NFTItem.Type = static_cast<ItemType>(PointsObject->GetIntegerField("type"));
					NFTItem.CollectionID = PointsObject->GetIntegerField("collection_id");
					NFTItem.Minted = PointsObject->GetBoolField("minted");
					NFTItem.ItemImage = PointsObject->GetStringField("image_url");
					NFTItem.ItemLevel = PointsObject->GetIntegerField("level");
					NFTItem.last_trip_id = PointsObject->GetIntegerField("last_trip_id");
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));

					TSharedPtr<FJsonObject> energy = PointsObject->GetObjectField("energy");
					NFTItem.capacity = energy->GetIntegerField("capacity"); // Byte
					NFTItem.spendPart = energy->GetIntegerField("spend_part");  // Byte
					NFTItem.active = energy->GetBoolField("active");
					UItem* AddedItem = NewObject<UItem>();
					AddedItem->SetItemInfo(NFTItem);
					GameMode->GetNFTItemManager()->AddItem(AddedItem);
				}
			}
		}
	}
}

void UHTTPAPIComponent::OnResponseReceivedActivation(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
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
		ErrorID = Response->GetResponseCode();
		bSuccess = true;
		Message = ResponseObject->GetStringField("message");
		if (ErrorID == 200)
		{
			bSuccess = ResponseObject->GetBoolField("success");
			if (bSuccess == true)
			{
				PathID = ResponseObject->GetNumberField("data");

				USpeedUpGameInstance* GameIst = (USpeedUpGameInstance*)GetWorld()->GetGameInstance();
				if (GameIst->UserInfo.Energy.spend_part > 0)
				{
					GameIst->UserInfo.Energy.spend_part = GameIst->UserInfo.Energy.spend_part - 1;
					GameIst->UserInfo.Energy.capacity -= - 1;
				}
				//int ErrorActivation;
				AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
				int TActivationItem = ActivationItem;
				int TPathID = PathID; 
				int ErrorActivation;

				//GameMode->GetNFTItemManager()->UpdateLastPathID(ActivationItem, PathID);
				GameMode->GetNFTItemManager()->ActivateItem(ActivationItem, PathID, 0, ErrorActivation);
				GameMode->GetGeoDataSystemCPP()->StartTrackPath(ActivationItem, PathID, 0);
				StartPath(ActivationItem, PathID);

				ActivationItem = -1;
			}
		}
	}
}

void UHTTPAPIComponent::OnResponseReceivedUpdate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
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
		ErrorID = Response->GetResponseCode();
		bSuccess = true;
		Message = ResponseObject->GetStringField("message");
		if (ErrorID == 200)
		{
			bSuccess = ResponseObject->GetBoolField("success");
			if (bSuccess == true)
			{
			}
		}
	}
}

void UHTTPAPIComponent::OnResponseReceivedRepairPassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	int Code = Response->GetResponseCode();
	if (Code != 200)
	{
		Message = "Wrong Password";
		return;
	}

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = 101;
		ErrorText = "Response is null";
	}
	//if (Code = 500)
	else
	{
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		//Message = ResponseObject->GetStringField("message");
		//Data = ResponseObject->GetStringField("data");
	}
}

void UHTTPAPIComponent::OnResponseReceivedRecoveryCode(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	int Code = Response->GetResponseCode();
	if (Code != 200)
	{
		Message = "Wrong Password";
		//return;
	}

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
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		//Data = ResponseObject->GetStringField("data");
	}
}

void UHTTPAPIComponent::OnResponseReceivedPathStatistick(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{
	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());

	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = Response->GetResponseCode();
		ErrorText = "Response is null";
	}
	else
	{
		if (SpeedUpGI)
		{
			//gameInstance->GetSaveManager()->FlushCachedSaveData();
			//UGameplayStatics::OpenLevel(world, FName(*world->GetName()));
			//UGameplayStatics::GetGameInstance()
			//TSharedPtr<FJsonObject> ObjectResult;

			ErrorID = Response->GetResponseCode();
			ErrorText = "";
			Message = ResponseObject->GetStringField("message");
			bSuccess = ResponseObject->GetBoolField("success");

			//TSharedPtr<FJsonObject> NFT = ResponseObject->GetObjectField("data");
			//TMap<FString, TSharedPtr<FJsonValue, ESPMode::ThreadSafe>> MapNFT = NFT->Values;
			//TArray<TSharedPtr<FJsonValue>> Points = NFT->GetArrayField(TEXT("Sneaker"));

			TSharedPtr<FJsonObject> PathData = ResponseObject->GetObjectField("data");
			TMap<FString, TSharedPtr<FJsonValue, ESPMode::ThreadSafe>> MapStatistic = PathData->Values;
			TSharedPtr<FJsonObject> tripsObject = MapStatistic["trips"]->AsObject();
			//TArray<TSharedPtr<FJsonValue>> tripsObject = PathData->GetArrayField(TEXT("trips"));
			TArray<TSharedPtr<FJsonValue>> SneakerPath = tripsObject->GetArrayField(TEXT("Sneaker"));
			if (SneakerPath.Num() > 0)
			{
				for (int32 i = 0; i < SneakerPath.Num(); ++i)
				{
					FItemStatistic ItemStat;
					TSharedPtr<FJsonObject> PointsObject = SneakerPath[i]->AsObject();

					ItemStat.id = PointsObject->GetIntegerField("id");
					ItemStat.user_id = PointsObject->GetIntegerField("user_id");

					TSharedPtr<FJsonObject> nft = PointsObject->GetObjectField("nft");
					ItemStat.nft = nft->GetIntegerField("id");
					ItemStat.Type = static_cast<ItemType>(nft->GetIntegerField("type"));
					ItemStat.ItemLevel = nft->GetIntegerField("level");
					ItemStat.ItemRarity = static_cast<ItemLevelRarity>(nft->GetIntegerField("rarity"));

					ItemStat.avg_velocity = PointsObject->GetNumberField("avg_velocity");
					ItemStat.avg_distance = PointsObject->GetNumberField("avg_distance");
					ItemStat.started_at = PointsObject->GetStringField("started_at");
					ItemStat.ended_at = PointsObject->GetStringField("ended_at");

					GameMode->GetNFTItemManager()->MyItemStatistic.Add(ItemStat);
				}
			}

			TArray<TSharedPtr<FJsonValue>> CarPath = tripsObject->GetArrayField(TEXT("Car"));
			if (CarPath.Num() > 0)
			{
				for (int32 i = 0; i < CarPath.Num(); ++i)
				{
					FItemStatistic ItemStat;
					TSharedPtr<FJsonObject> PointsObject = CarPath[i]->AsObject();

					ItemStat.id = PointsObject->GetIntegerField("id");
					ItemStat.user_id = PointsObject->GetIntegerField("user_id");

					TSharedPtr<FJsonObject> nft = PointsObject->GetObjectField("nft");
					ItemStat.nft = nft->GetIntegerField("id");
					ItemStat.Type = static_cast<ItemType>(nft->GetIntegerField("type"));
					ItemStat.ItemLevel = nft->GetIntegerField("level");
					ItemStat.ItemRarity = static_cast<ItemLevelRarity>(nft->GetIntegerField("rarity"));

					ItemStat.avg_velocity = PointsObject->GetNumberField("avg_velocity");
					ItemStat.avg_distance = PointsObject->GetNumberField("avg_distance");
					ItemStat.started_at = PointsObject->GetStringField("started_at");
					ItemStat.ended_at = PointsObject->GetStringField("ended_at");

					GameMode->GetNFTItemManager()->MyItemStatistic.Add(ItemStat);
				}
			}

			TArray<TSharedPtr<FJsonValue>> PlanePath = tripsObject->GetArrayField(TEXT("Car"));
			if (PlanePath.Num() > 0)
			{
				for (int32 i = 0; i < PlanePath.Num(); ++i)
				{
					FItemStatistic ItemStat;
					TSharedPtr<FJsonObject> PointsObject = PlanePath[i]->AsObject();

					ItemStat.id = PointsObject->GetIntegerField("id");
					ItemStat.user_id = PointsObject->GetIntegerField("user_id");

					TSharedPtr<FJsonObject> nft = PointsObject->GetObjectField("nft");
					ItemStat.nft = nft->GetIntegerField("id");
					ItemStat.Type = static_cast<ItemType>(nft->GetIntegerField("type"));
					ItemStat.ItemLevel = nft->GetIntegerField("level");
					ItemStat.ItemRarity = static_cast<ItemLevelRarity>(nft->GetIntegerField("rarity"));

					ItemStat.avg_velocity = PointsObject->GetNumberField("avg_velocity");
					ItemStat.avg_distance = PointsObject->GetNumberField("avg_distance");
					ItemStat.started_at = PointsObject->GetStringField("started_at");
					ItemStat.ended_at = PointsObject->GetStringField("ended_at");

					GameMode->GetNFTItemManager()->MyItemStatistic.Add(ItemStat);
				}
			}

			//TSharedPtr<FJsonObject> tripsObjectCar = trips[1]->AsObject();
			//TArray<TSharedPtr<FJsonValue>> Car = tripsObjectCar->GetArrayField(TEXT("Car"));

			//TSharedPtr<FJsonObject> tripsObjectPlane = trips[2]->AsObject();
			//TArray<TSharedPtr<FJsonValue>> Plane = tripsObjectPlane->GetArrayField(TEXT("Plane"));

				//Tarray<TSharedPtr<FJsonObject>> trips = Data->GetArrayField("trips");

				/*
				"id": 7,
				"user_id": 43,
				"nft": {
				"id": 11,
				"image_url": "",
				"type": 1,
				"collection_id": 0,
				"chain_id": 0,
				"level": 1,
				"rarity": 0,
				"meta": {},
				"minted": false,
				"last_trip_id": 0,
				"energy": {
						   "capacity": 0,
						   "spend_part": 0,
						   "active": false
				  }
						},
						"spent_energy": 0,
						"avg_velocity": 0,
						"avg_distance": 0,
						"started_at": "2022-11-05T16:48:42.809994Z",
						"ended_at": "2022-11-05T17:15:37.104547Z",
						"time": 0,
						"earned_dks": 0,
						"earned_internal": 0
				*/


				//FString Profile_Name = Sneaker->GetStringField("email");
				//int Profile_id = Sneaker->GetIntegerField("id");
				//bool Profile_email_confirmed = Sneaker->GetBoolField("email_confirmed");
				//int Allowed_slots = Sneaker->GetIntegerField("allowed_slots");
		}
	}
}

void UHTTPAPIComponent::OnResponseReceivedTransactions(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess)
{

	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();

	USpeedUpGameInstance* SpeedUpGI = Cast<USpeedUpGameInstance>(GetWorld()->GetGameInstance());

	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	if (ResponseObject == nullptr)
	{
		bSuccess = false;
		Message = "ResponseObject is null";
		Data = "";
		ErrorID = Response->GetResponseCode();
		ErrorText = "Response is null";
	}
	else
	{
		if (SpeedUpGI)
		{

			ErrorID = Response->GetResponseCode();
			ErrorText = "";
			Message = ResponseObject->GetStringField("message");
			bSuccess = ResponseObject->GetBoolField("success");



			/*"data": [
			{
					"earned_dks": 0,
					"earned_internal" : 36.6,
					"date" : "Saturday, 05-Nov-22 18:26:19 GMT",
					"tx_type" : 0
			}
			]
			*/


			//TSharedPtr<FJsonObject> Transactions = ResponseObject->GetObjectField("data");
			//TMap<FString, TSharedPtr<FJsonValue, ESPMode::ThreadSafe>> MapTransactions = Transactions->Values;
			TArray<TSharedPtr<FJsonValue>> operations = ResponseObject->GetArrayField("data");
			GameMode->GetWalletInfo()->MyHistory.Empty();
			for (int32 i = 0; i < operations.Num(); ++i)
			{
				//UWalletTransaction Transaction;
				UWalletTransaction* Transaction = NewObject<UWalletTransaction>();
				TSharedPtr<FJsonObject> PointsObject = operations[i]->AsObject();
				Transaction->distance = PointsObject->GetNumberField("distance");
				Transaction->earnedDKS = PointsObject->GetNumberField("earned_dks");
				Transaction->earnedInternalSPD = PointsObject->GetNumberField("earned_internal");
				Transaction->dateTransaction = PointsObject->GetStringField("date");
				//FString date = PointsObject->GetStringField("date");
				//Transaction.dateTransaction.ParseHttpDate(date, Transaction.dateTransaction);
				//printf(Transaction.dateTransaction);
				Transaction->TransactionType = PointsObject->GetIntegerField("tx_type");
				
				
				GameMode->GetWalletInfo()->AddTransaction(Transaction);
				


				//UItem* AddedItem = NewObject<UItem>();
				//AddedItem->SetItemInfo(NFTItem);
				//GameMode->GetNFTItemManager()->AddItem(AddedItem);



				//GameMode->GetNFTItemManager()->MyItemStatistic.Add(ItemStat);
				//UBaseWalletWidget* AddedTransactions = NewObject<UBaseWalletWidget>();
				//AddedTransactions->SetWalletInfo(Transaction);
				//GameMode->GetWalletInfo();


				//GameMode->GetBaseWalletWidget()
				//UItem* AddedItem = NewObject<UItem>();
				//AddedItem->SetItemInfo(NFTItem);
				//GameMode->GetNFTItemManager()->AddItem(AddedItem);
				

					//GameMode->GetNFTItemManager()->MyItemStatistic.Add(ItemStat);
					//GameMode->GetNFTItemManager()->AddItem(AddedItem);
			}

			//Points = NFT->GetArrayField(TEXT("Car"));
		}

	}
}
void UHTTPAPIComponent::OnResponseReceivedBuyingSlot(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessBuying)
{
	TSharedPtr<FJsonObject> ResponseObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, ResponseObject);

	int Code = Response->GetResponseCode();
	if (Code != 200)
	{
		Message = "Unsuccess";
	}

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
		ErrorID = 0;
		ErrorText = "";
		bSuccess = ResponseObject->GetBoolField("success");
		Message = ResponseObject->GetStringField("message");
		
	}

}
void UHTTPAPIComponent::StartPath_Implementation(int ItemID, int StartPathID)
{}
void UHTTPAPIComponent::StotPath_Implementation(int ItemID, int StopPathID)
{}

UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}