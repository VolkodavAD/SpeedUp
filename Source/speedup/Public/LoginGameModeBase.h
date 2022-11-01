// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "..\Public\HTTPAPIComponent.h"
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
	//class USkeletalMeshComponent* MeshBody;

public:
	//FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }
	//UFUNCTION(BlueprintNativeEvent, Category = "mesh")
	FORCEINLINE class UHTTPAPIComponent* GeHTTP() const { return HTTP; }
};
