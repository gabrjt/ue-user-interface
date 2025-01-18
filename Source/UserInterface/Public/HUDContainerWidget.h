#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "HUDContainerWidget.generated.h"

class UFriendListWidget;
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

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendListViewModelDataAsset> ConnectedFriendsDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UFriendListViewModelDataAsset> DisconnectedFriendsDataAsset;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetViewModels(UFriendListWidget*    ConnectedFriendsWidget,
	                   UFriendListViewModel* ConnectedFriendsViewModel,
	                   UFriendListWidget*    DisconnectedFriendsWidget,
	                   UFriendListViewModel* DisconnectedFriendsViewModel);

private:
	void OnDataAssetsLoaded() const;
};
