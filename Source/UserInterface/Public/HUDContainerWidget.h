#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HUDContainerWidget.generated.h"

class UFriendListWidget;
class UConnectedFriendListWidget;
class UFriendListViewModel;
class UFriendListViewModelDataAsset;

UCLASS()
class USERINTERFACE_API UHUDContainerWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendListWidget* ConnectedFriends;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendListWidget* DisconnectedFriends;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UConnectedFriendListWidget* ConnectedFriendsNotifications;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendListViewModelDataAsset> ConnectedFriendsDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendListViewModelDataAsset> DisconnectedFriendsDataAsset;

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnDataAssetsLoaded() const;
};
