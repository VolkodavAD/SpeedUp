// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"


ALoginGameModeBase::ALoginGameModeBase()
{
	HTTP = CreateDefaultSubobject<UHTTPAPIComponent>(TEXT("HTTP"));
	//NFTItemManager->AddToRoot();
	//MeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//NFTItemManager->RegisterComponent();
}