#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HUDContainerWidget.generated.h"

class UFriendsWidget;
class UFriendsNotificationsWidget;
class UFriendListViewModel;
class UFriendsWidgetViewModelDataAsset;

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

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendsWidgetViewModelDataAsset> ConnectedFriendsDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendsWidgetViewModelDataAsset> DisconnectedFriendsDataAsset;

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnDataAssetsLoaded() const;
};
