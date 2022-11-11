// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Json.h" 
#include "Items/Item.h"
#include "UObject/Object.h"
#include "Interfaces/IHttpRequest.h"
#include "HTTPAPIComponent.generated.h"

class UActorComponent;
class AspeedupGameModeBase;
class USpeedUpGameInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPEEDUP_API UHTTPAPIComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	void OnResponseReceivedSignUP(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedSignIN(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedLogOut(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedSendCode(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	//void OnResponseReceivedSendCode(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedVerefi(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedChangePassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);

	void OnResponseReceivedProfile(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedActivation(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedNFTreceipt(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedUpdate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedRepairPassword(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedRecoveryCode(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);

	void OnResponseReceivedPathStatistick(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);

	void OnResponseReceivedTransactions(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bLoginSuccess);
	void OnResponseReceivedBuyingSlot(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessBuying);
	void OnResponseReceivedNFTlevelUp(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessLvlUp);

	const FString SignUPURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/signup";
	const FString SignINURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/login";
	const FString LogOutURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/logout";
	const FString ChangePasswordURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/change-password";
	const FString PasswordRepairURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/recovery-account";
	const FString SendRecoveryCodeURL = "https://m2e-backend-auth.production.bc.gotbitgames.co/auth/send-code-recovery";

	const FString SendCodeURL =	"https://m2e-backend-auth.production.bc.gotbitgames.co/auth/send-code";
	const FString VerifiURL =	"https://m2e-backend-auth.production.bc.gotbitgames.co/auth/verify-code";

	const FString ProfileURL =		"https://m2e-backend-core.production.bc.gotbitgames.co/profile";
	const FString StatisticURL = "https://m2e-backend-core.production.bc.gotbitgames.co/profile/stat";
	const FString TransactionsURL = "https://m2e-backend-core.production.bc.gotbitgames.co/profile/transactions/history";
	
	const FString NFTreceiptRequestURL =	"https://m2e-backend-core.production.bc.gotbitgames.co/profile/nfts";
	const FString NFTActiveRequestURL =		"https://m2e-backend-core.production.bc.gotbitgames.co/start";
	const FString NFTDeactiveRequestURL =	"https://m2e-backend-core.production.bc.gotbitgames.co/stop";
	const FString NFTUpdateRequestURL =		"https://m2e-backend-core.production.bc.gotbitgames.co/update-params";
	const FString BuyingSlotURL = "https://m2e-backend-core.production.bc.gotbitgames.co/profile/slot/buy";
	const FString NFTlevelUpURL = "https://m2e-backend-core.production.bc.gotbitgames.co/profile/nft/up";
	
	///update-params
	//NFTreceiptRequestURL

	int ActivationItem = -1;
public:

	UHTTPAPIComponent();

	UPROPERTY(BlueprintReadOnly)
	FString LoginResult;

	UPROPERTY(BlueprintReadOnly)
	bool bSuccess;
	
	UPROPERTY(BlueprintReadOnly)
	FString Message;
	
	UPROPERTY(BlueprintReadOnly)
	FString Data;

	UPROPERTY(BlueprintReadOnly)
	int PathID;


	USpeedUpGameInstance* GI;

	UPROPERTY(BlueprintReadOnly)
	int ErrorID;
	UPROPERTY(BlueprintReadOnly)
	FString ErrorText;
	UPROPERTY(BlueprintReadOnly)
	FString ClientEmail;
	UPROPERTY(BlueprintReadOnly)
	FString ClientTocken;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitComponent();

	UFUNCTION(BlueprintCallable)
	void SignUpRequest(const FString Email, const FString Password);

	UFUNCTION(BlueprintCallable)
	void SignInRequest(const FString Email, const FString Password);

	UFUNCTION(BlueprintCallable)
	void ChangePassword(const FString OldPassword, const FString NewPassword, const FString TokenData);

	UFUNCTION(BlueprintCallable)
	void RepairPassword(const FString NewPassword, const FString RecoveryCode, const FString Email);

	UFUNCTION(BlueprintCallable)
	void SendRecoveryCode(const FString Email);

	UFUNCTION(BlueprintCallable)
	void LogoutRequest(const FString DataToken);

	UFUNCTION(BlueprintCallable)
	void CodeRequestFromServer(const FString DataToken);

	UFUNCTION(BlueprintCallable)
	void NFTreceiptRequest(const FString TokenData);

	UFUNCTION(BlueprintCallable)
	void NFTactivationRequest(const int ActivNFDId);

	UFUNCTION(BlueprintCallable)
	void NFTdeactivationRequest(const int DeactivePathID, const int DeactivNFDId, const float avg_velocity, const float avg_distance);

	UFUNCTION(BlueprintCallable)
	void NFTUpdateRequest(const int DeactivePathID, const int DeactivNFDId, const float avg_velocity, const float avg_distance);

	UFUNCTION(BlueprintCallable)
	void StatisticRequest(const ItemType StatItemType, const int Period);

	UFUNCTION(BlueprintCallable)
		void TransactionsRequest(const int Page, const int Limit, const FString TokenData);

	UFUNCTION(BlueprintCallable)
		void BuyingSlotRequest(const FString TokenData);

	UFUNCTION(BlueprintCallable)
		void NFTlevelUpRequest(const int NFTid, const FString TokenData);


	UFUNCTION(BlueprintNativeEvent)
	void StartPath(int ItemID, int StartPathID);
	void StartPath_Implementation(int ItemID, int StartPathID);
	UFUNCTION(BlueprintNativeEvent)
	void StotPath(int ItemID, int StopPathID);
	void StotPath_Implementation(int ItemID, int StopPathID);

	UFUNCTION(BlueprintCallable)
	void Verify(const FString CodeFromMail, const FString TokenData);
	UFUNCTION(BlueprintCallable)
	void Profile(const FString TokenData);
};
