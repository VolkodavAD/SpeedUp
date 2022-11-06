// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "..\Public\HTTPAPIComponent.h"
#include "Items/ItemManager.h"
#include "GeoData/Speedup_GeoDataSystem.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDUP_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ALoginGameModeBase();

protected:
	//UItemManager* NFTItemManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UHTTPAPIComponent* HTTP;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	class UItemManager* NFTItemManager;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	class USpeedup_GeoDataSystem* GeoDataSystemCPP;

public:
	FORCEINLINE class UHTTPAPIComponent* GeHTTP() const { return HTTP; }
	//FORCEINLINE class UItemManager* GetNFTItemManager() const { return NFTItemManager; }
	//FORCEINLINE class USpeedup_GeoDataSystem* GetGeoDataSystemCPP() const { return GeoDataSystemCPP; }
};
