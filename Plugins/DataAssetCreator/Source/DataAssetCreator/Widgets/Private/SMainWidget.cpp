#include "SMainWidget.h"
#include "AssetToolsModule.h"
#include "EngineUtils.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "SlateOptMacros.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "SampleDataAsset.h"
#include "UObject/SavePackage.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"

void CreateNewAsset()
{
	//load FAssetToolsModule
	const FAssetToolsModule& _assetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");

	//get the asset tools
	IAssetTools& _assetTools = _assetToolsModule.Get();

	//get unique names for both the asset and the package
	const FString _assetName = "NewSampleDataAsset";
	const FString _packageName = "/Game/DataAssets/";
	FString _uniqueAssetName = "";
	FString _uniquePackageName = "";
	_assetTools.CreateUniqueAssetName(_packageName, _assetName, _uniquePackageName, _uniqueAssetName);

	//create and load the package
	UPackage* _package = CreatePackage(*_uniquePackageName);
	checkf(_package, TEXT("[SMainWidget::CreateNewAsset] Failed to create the package"));
	_package->FullyLoad();

	//instantiate the data asset
	USampleDataAsset* _dataAsset = NewObject<USampleDataAsset>(_package, *_uniqueAssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	_dataAsset->AddToRoot();

	//mark the package dirty
	_package->MarkPackageDirty();

	//save the asset
	FAssetRegistryModule::AssetCreated(_dataAsset);
	FSavePackageArgs _savePackageArgs = {};
	_savePackageArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	_savePackageArgs.bForceByteSwapping = true;
	_savePackageArgs.SaveFlags = SAVE_NoError;
	const FString _packageFileName = FPackageName::LongPackageNameToFilename(_uniquePackageName, FPackageName::GetAssetPackageExtension());
	const bool _saved = UPackage::SavePackage(_package, _dataAsset, *_packageFileName, _savePackageArgs);
	// const bool _saved = UPackage::SavePackage(_package, _dataAsset, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *_packageFileName, GError, nullptr, true, true, SAVE_NoError);
	checkf(_saved, TEXT("Failed To Save Data Asset"))
}

void DeleteAllAssets()
{
	TArray<UObject*> _loadedAssets{};
	if(!EngineUtils::FindOrLoadAssetsByPath("/Game/DataAssets/", _loadedAssets, EngineUtils::EAssetToLoad::ATL_Regular))
		return;
	for (int i = 0; i < _loadedAssets.Num(); ++i)
	{
		if (Cast<USampleDataAsset>(_loadedAssets[i]))
			continue;
		_loadedAssets.RemoveAt(i);
		--i;
	}
	ObjectTools::DeleteObjects(_loadedAssets);
}

void DeleteAllAssets2()
{
	TArray<FString> _assets = UEditorAssetLibrary::ListAssets("/Game/DataAssets");
	for (const FString& _asset : _assets)
		if (USampleDataAsset* _dataAsset = Cast<USampleDataAsset>(UEditorAssetLibrary::LoadAsset(_asset)))
			UEditorAssetLibrary::DeleteLoadedAsset(_dataAsset);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMainWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Create SampleDataAsset"))
				.OnClicked_Lambda
				             ([]
				             {
					             CreateNewAsset();
					             return FReply::Handled();
				             })
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Delete All SampleDataAssets Method 1"))
				.OnClicked_Lambda
							 ([]
							 {
								 DeleteAllAssets();
								 return FReply::Handled();
							 })
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Delete All SampleDataAssets Method 2"))
				.OnClicked_Lambda
							 ([]
							 {
								 DeleteAllAssets2();
								 return FReply::Handled();
							 })
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
