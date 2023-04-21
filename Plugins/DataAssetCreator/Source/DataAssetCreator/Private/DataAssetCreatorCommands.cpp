// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataAssetCreatorCommands.h"

#define LOCTEXT_NAMESPACE "FDataAssetCreatorModule"

void FDataAssetCreatorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DataAssetCreator", "Bring up DataAssetCreator window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
