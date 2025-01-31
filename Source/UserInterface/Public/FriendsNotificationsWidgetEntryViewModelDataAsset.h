#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateColor.h"
#include "FriendsNotificationsWidgetEntryViewModelDataAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class USERINTERFACE_API UFriendsNotificationsWidgetEntryViewModelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "View Model Settings")
	FSlateColor NicknameTextColor;

	UPROPERTY(EditDefaultsOnly, Category = "View Model Settings")
	FString NotificationText;
};
