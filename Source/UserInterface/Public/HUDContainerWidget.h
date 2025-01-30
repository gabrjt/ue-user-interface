#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HUDContainerWidget.generated.h"

class UFriendsWidget;
class UFriendsWidgetViewModelDataAsset;
class UFriendsNotificationsWidget;

UCLASS()
class USERINTERFACE_API UHUDContainerWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendsWidget* ConnectedFriends;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendsWidget* DisconnectedFriends;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendsNotificationsWidget* ConnectedFriendsNotifications;
};
