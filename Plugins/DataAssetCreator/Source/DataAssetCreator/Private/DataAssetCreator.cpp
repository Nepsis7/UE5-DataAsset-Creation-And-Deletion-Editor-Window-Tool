// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataAssetCreator.h"
#include "DataAssetCreatorStyle.h"
#include "DataAssetCreatorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SMainWidget.h"

static const FName DataAssetCreatorTabName("DataAssetCreator");

#define LOCTEXT_NAMESPACE "FDataAssetCreatorModule"

void FDataAssetCreatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FDataAssetCreatorStyle::Initialize();
	FDataAssetCreatorStyle::ReloadTextures();

	FDataAssetCreatorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDataAssetCreatorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDataAssetCreatorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDataAssetCreatorModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DataAssetCreatorTabName, FOnSpawnTab::CreateRaw(this, &FDataAssetCreatorModule::OnSpawnPluginTab))
	                        .SetDisplayName(LOCTEXT("FDataAssetCreatorTabTitle", "DataAssetCreator"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDataAssetCreatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDataAssetCreatorStyle::Shutdown();

	FDataAssetCreatorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DataAssetCreatorTabName);
}

TSharedRef<SDockTab> FDataAssetCreatorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SMainWidget)
		];
}

void FDataAssetCreatorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DataAssetCreatorTabName);
}

void FDataAssetCreatorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDataAssetCreatorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDataAssetCreatorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDataAssetCreatorModule, DataAssetCreator)
