// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetManager.h"

bool UWidgetManager::AddWidget(FString name, TSubclassOf<UBaseSpeedUpWidget> widgetClass, int zOrder)
{
   /* if (!widgetClass)
        return false;
    if (widgets.Contains(name))
        return false;
    FWidgetInfo info = { widgetClass, nullptr, zOrder };
    widgets.Add(name, info);
    return true;*/
    return true;
}

//void UWidgetManager::InitAndStartCaching(USpeedUpGameInstance* gi)
//{
//    for (auto& widget_pair : widgets)
//    {
//        auto& widgetInfo = widget_pair.Value;
//        auto& name = widget_pair.Key;
//        widgetInfo.widget = CreateWidget<UBaseSpeedUpWidget>(gi, widgetInfo.widgetClass, *(FString("W_") + name));
//        widgetInfo.widget->gi = gi;
//        widgetInfo.widget->AddToViewport(widgetInfo.zOrder);
//        if (widgetInfo.widget->needsCaching)
//        {
//            widgetInfo.widget->StartCache();
//        }
//        else
//            widgetInfo.widget->Hide();
//    }
//}

//void UWidgetManager::EndCaching()
//{
//    for (auto& widget_pair : widgets)
//    {
//        auto& widgetInfo = widget_pair.Value;
//        auto& name = widget_pair.Key;
//        if (widgetInfo.widget->needsCaching)
//        {
//            widgetInfo.widget->EndCache();
//        }
//        if (widgetInfo.widget->hideAfterCache)
//            widgetInfo.widget->SetVisibility(ESlateVisibility::Collapsed);
//    }
//}

bool UWidgetManager::ShowWidget(FString name)
{
    if (!widgets.Contains(name))
        return false;
    auto& widgetInfo = widgets[name];
    if (widgetInfo.widget)
        widgetInfo.widget->Show();
    return true;
}

bool UWidgetManager::HideWidget(FString name)
{
    if (!widgets.Contains(name))
        return false;
    auto& widgetInfo = widgets[name];
    if (widgetInfo.widget)
        widgetInfo.widget->Hide();

    return true;
}

UBaseSpeedUpWidget* UWidgetManager::GetWidget(FString name)
{
    if (!widgets.Contains(name))
        return nullptr;
    return widgets[name].widget;
}

UBaseSpeedUpWidget* UWidgetManager::CreateTransientWidget(TSubclassOf<UBaseSpeedUpWidget> widgetClass, UWorld* world, FString name)
{
    return nullptr;
}
