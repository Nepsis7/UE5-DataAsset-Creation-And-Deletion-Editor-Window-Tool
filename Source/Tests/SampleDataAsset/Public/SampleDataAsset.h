#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SampleDataAsset.generated.h"

UCLASS()
class TESTS_API USampleDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int testValue = 3;
};
