// Fill out your copyright notice in the Description page of Project Settings.

#include "HTTPAPIComponent.h"
#include "HttpModule.h"
#include "Items/Item.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "SpeedUpGameInstance.h" 
#include "..\speedupGameModeBase.h"
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

void UHTTPAPIComponent::NFTreceiptRequest(const FString TokenData)
{
	const FHttpRequestRef NFTget = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	
	FString BearerT = "Bearer ";
	NFTget->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedNFTreceipt);
	NFTget->SetURL(NFTreceiptRequestURL);
	NFTget->SetVerb("GET");
	NFTget->SetHeader("Content-Type", "application/json");
	NFTget->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	
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

void UHTTPAPIComponent::NFTdeactivationRequest(const int DeactivNFDId)
{

	USpeedUpGameInstance* GameIst = (USpeedUpGameInstance*)GetWorld()->GetGameInstance();
	AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
	UItem* DeactivNFDIdItem = GameMode->GetNFTItemManager()->GetMyItem(DeactivNFDId);

	const FHttpRequestRef RequestActiveNFT = FHttpModule::Get().CreateRequest();

	const TSharedRef<FJsonObject> NFTJsonObject = MakeShared<FJsonObject>();
	NFTJsonObject->SetNumberField("id", DeactivNFDId);
	NFTJsonObject->SetNumberField("Type", (int)DeactivNFDIdItem->GetType());

	const TSharedRef<FJsonObject> RequestJsonObject = MakeShared<FJsonObject>();
	RequestJsonObject->SetNumberField("id", GameIst->UserInfo.id);
	RequestJsonObject->SetObjectField("nft_id", NFTJsonObject);

	NFTJsonObject->SetNumberField("avg_velosity", 4);
	NFTJsonObject->SetNumberField("avg_distanse", 50);

	//токен
	//RequestJsonObject->SetStringField("token", Password);
	FString RequestBody;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestJsonObject, JsonWriter);

	FString BearerT = "Bearer ";
	RequestActiveNFT->OnProcessRequestComplete().BindUObject(this, &UHTTPAPIComponent::OnResponseReceivedActivation);
	RequestActiveNFT->SetURL(NFTDeactiveRequestURL);
	RequestActiveNFT->SetVerb("POST");
	RequestActiveNFT->SetHeader("Content-Type", "application/json");
	RequestActiveNFT->AppendToHeader("Authorization", BearerT.Append(ClientTocken));
	RequestActiveNFT->SetContentAsString(RequestBody);

	RequestActiveNFT->ProcessRequest();

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
	}
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("success : %s"), *ResponseObject->GetStringField("success"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("message : %s"), *ResponseObject->GetStringField("message"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("data : %s"), *ResponseObject->GetStringField("data"))
	//UE_LOG(HTTP_REQUEST_RESPONSE, Log, TEXT("Response : %s"), *Response->GetContentAsString())
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

				ErrorID = 0;
				ErrorText = "";
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
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));

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
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));

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
					NFTItem.ItemRarity = static_cast<ItemLevelRarity>(PointsObject->GetIntegerField("rarity"));

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
		bSuccess = true;
		ErrorID = 0;

		Message = ResponseObject->GetStringField("message");
		bSuccess = ResponseObject->GetBoolField("success");
		if (bSuccess == true)
		{
			PathID = ResponseObject->GetNumberField("data");

			USpeedUpGameInstance* GameIst = (USpeedUpGameInstance*)GetWorld()->GetGameInstance();
			if (GameIst->UserInfo.Energy.spend_part > 0)
			{
				GameIst->UserInfo.Energy.spend_part = GameIst->UserInfo.Energy.spend_part - 1;
			}

			int ErrorActivation;
			AspeedupGameModeBase* GameMode = (AspeedupGameModeBase*)GetWorld()->GetAuthGameMode();
			GameMode->GetNFTItemManager()->ActivateItem(ActivationItem, PathID, 0, ErrorActivation);

			ActivationItem = -1;

		}
	}
}


UHTTPAPIComponent::UHTTPAPIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}