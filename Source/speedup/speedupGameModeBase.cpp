// Fill out your copyright notice in the Description page of Project Settings.

#include "speedupGameModeBase.h"
#include "Components/ActorComponent.h"

AspeedupGameModeBase::AspeedupGameModeBase()
{
	NFTItemManager = CreateDefaultSubobject<UItemManager>(TEXT("ItemManager")); 
	//NFTItemManager->AddToRoot();
	//MeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//NFTItemManager->RegisterComponent();
}