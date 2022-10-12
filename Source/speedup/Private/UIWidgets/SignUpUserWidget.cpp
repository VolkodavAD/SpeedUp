// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgets/SignUpUserWidget.h"
#include "HttpModule.h"


/*
void USignUpUserWidget::MakeRequest()
{
	FHttpModule* Module = &FHttpModule::Get();
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> Request = Module->CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this,&ThisClass::OnPostReceivedResponse);// Подвязываемся на делегат получения запроса.
	Request->SetURL(GetFullPathURL()); //Выставляем URL. В моем случае - абстрактный путь куда-нибудь
	Request->SetVerb("POST"); //Непосредственно сам глагол.
	Request->SetHeader(GetDefaultHeader().Key,GetDefaultHeader().Value);//Опять же, абстрактный хеддер. В вашем случае все зависит от API.
	Request->SetContentAsString(GetContent());//Абстрактная строка, некогда бывшая Json файлом. (Об этом Ниже).
	Request->ProcessRequest(); // Отправляем запрос.
}
*/
