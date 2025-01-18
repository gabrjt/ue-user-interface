#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateColor.h"
#include "Types/SlateEnums.h"
#include "FriendListViewModelDataAsset.generated.h"

UCLASS()
class USERINTERFACE_API UFriendListViewModelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "View Model Settings")
	FString Title;

	UPROPERTY(EditDefaultsOnly, Category = "View Model Settings")
	FSlateColor TextColor;

	UPROPERTY(EditDefaultsOnly, Category = "View Model Settings")
	ESlateVisibility Visibility;
};
