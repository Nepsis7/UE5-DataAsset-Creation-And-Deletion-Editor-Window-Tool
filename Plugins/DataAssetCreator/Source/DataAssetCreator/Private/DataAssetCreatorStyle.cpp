// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataAssetCreatorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FDataAssetCreatorStyle::StyleInstance = nullptr;

void FDataAssetCreatorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FDataAssetCreatorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FDataAssetCreatorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DataAssetCreatorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FDataAssetCreatorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("DataAssetCreatorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("DataAssetCreator")->GetBaseDir() / TEXT("Resources"));

	Style->Set("DataAssetCreator.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FDataAssetCreatorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FDataAssetCreatorStyle::Get()
{
	return *StyleInstance;
}
