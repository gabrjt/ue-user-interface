#include "HUDContainerWidget.h"
#include "FriendListViewModel.h"
#include "FriendListViewModelDataAsset.h"
#include "FriendListWidget.h"
#include "FriendViewModelSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UHUDContainerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConnectedFriends->SetVisibility(ESlateVisibility::Hidden);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Hidden);

	const UFriendViewModelSubsystem* FriendViewModelSubsystem { GetGameInstance()->GetSubsystem<UFriendViewModelSubsystem>() };

	SetViewModels(ConnectedFriends,
		FriendViewModelSubsystem->GetConnectedFriendsViewModel(),
		DisconnectedFriends,
		FriendViewModelSubsystem->GetDisconnectedFriendsViewModel());

	TArray              AssetsToLoad { ConnectedFriendsDataAsset.ToSoftObjectPath(), DisconnectedFriendsDataAsset.ToSoftObjectPath() };
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &UHUDContainerWidget::OnDataAssetsLoaded));
}

void UHUDContainerWidget::OnDataAssetsLoaded()
{
	const UFriendViewModelSubsystem* FriendViewModelSubsystem { GetGameInstance()->GetSubsystem<UFriendViewModelSubsystem>() };
	UFriendListViewModel*            ConnectedFriendsViewModel { FriendViewModelSubsystem->GetConnectedFriendsViewModel() };
	UFriendListViewModel*            DisconnectedFriendsViewModel { FriendViewModelSubsystem->GetDisconnectedFriendsViewModel() };

	ConnectedFriendsViewModel->Set(ConnectedFriendsDataAsset.Get());
	DisconnectedFriendsViewModel->Set(DisconnectedFriendsDataAsset.Get());

	ConnectedFriends->SetVisibility(ESlateVisibility::Visible);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Visible);

	ViewModelsDataLoaded(ConnectedFriends, ConnectedFriendsViewModel, DisconnectedFriends, DisconnectedFriendsViewModel);
}
