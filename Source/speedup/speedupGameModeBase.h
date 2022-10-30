// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Items/ItemManager.h"
#include "speedupGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDUP_API AspeedupGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AspeedupGameModeBase();

protected:
	//UItemManager* NFTItemManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UItemManager* NFTItemManager;
	//class USkeletalMeshComponent* MeshBody;

public:
	//FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }
	//UFUNCTION(BlueprintNativeEvent, Category = "mesh")
	FORCEINLINE class UItemManager* GetNFTItemManager() const { return NFTItemManager; }
};
