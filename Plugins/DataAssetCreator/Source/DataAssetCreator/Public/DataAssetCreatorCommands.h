// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DataAssetCreatorStyle.h"

class FDataAssetCreatorCommands : public TCommands<FDataAssetCreatorCommands>
{
public:

	FDataAssetCreatorCommands()
		: TCommands<FDataAssetCreatorCommands>(TEXT("DataAssetCreator"), NSLOCTEXT("Contexts", "DataAssetCreator", "DataAssetCreator Plugin"), NAME_None, FDataAssetCreatorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};