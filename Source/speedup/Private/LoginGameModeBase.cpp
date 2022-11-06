// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"


ALoginGameModeBase::ALoginGameModeBase()
{
	HTTP = CreateDefaultSubobject<UHTTPAPIComponent>(TEXT("HTTP"));
	//NFTItemManager = CreateDefaultSubobject<UItemManager>(TEXT("ItemManager"));
	//GeoDataSystemCPP = CreateDefaultSubobject<USpeedup_GeoDataSystem>(TEXT("GeoDataSystemCPP"));
	
	//HTTP->RegisterComponent(); //?
	//NFTItemManager->RegisterComponent();
}