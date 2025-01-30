#include "HUDContainerWidget.h"
#include "ConnectedFriendListViewModel.h"
#include "ConnectedFriendListWidget.h"
#include "FriendListViewModelBase.h"
#include "FriendListViewModelDataAsset.h"
#include "FriendListWidget.h"
#include "FriendViewModelSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UHUDContainerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const UFriendViewModelSubsystem* FriendViewModelSubsystem { GetGameInstance()->GetSubsystem<UFriendViewModelSubsystem>() };

	ConnectedFriends->SetVisibility(ESlateVisibility::Hidden);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Hidden);
	ConnectedFriends->SetViewModel(FriendViewModelSubsystem->GetConnectedFriendsViewModel());
	DisconnectedFriends->SetViewModel(FriendViewModelSubsystem->GetDisconnectedFriendsViewModel());
	ConnectedFriendsNotifications->SetViewModel(FriendViewModelSubsystem->GetFriendsNotificationsViewModel());

	TArray              AssetsToLoad { ConnectedFriendsDataAsset.ToSoftObjectPath(), DisconnectedFriendsDataAsset.ToSoftObjectPath() };
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UHUDContainerWidget::OnDataAssetsLoaded));
}

void UHUDContainerWidget::OnDataAssetsLoaded() const
{
	ConnectedFriends->SetVisibility(ESlateVisibility::Visible);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Visible);

	ConnectedFriends->ViewModelDataLoaded(ConnectedFriendsDataAsset.Get());
	DisconnectedFriends->ViewModelDataLoaded(DisconnectedFriendsDataAsset.Get());
}
