#include "HUDContainerWidget.h"
#include "FriendsNotificationsWidget.h"
#include "FriendsViewModelSubsystem.h"
#include "FriendsWidget.h"
#include "FriendsWidgetViewModelDataAsset.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UHUDContainerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const UFriendsViewModelSubsystem* FriendViewModelSubsystem {
		GetGameInstance()->GetSubsystem<UFriendsViewModelSubsystem>()
	};

	ConnectedFriends->SetVisibility(ESlateVisibility::Hidden);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Hidden);
	ConnectedFriends->SetViewModel(FriendViewModelSubsystem->GetConnectedFriendsViewModel());
	DisconnectedFriends->SetViewModel(FriendViewModelSubsystem->GetDisconnectedFriendsViewModel());
	ConnectedFriendsNotifications->SetViewModel(FriendViewModelSubsystem->GetFriendsNotificationsViewModel());

	TArray AssetsToLoad {
		ConnectedFriendsDataAsset.ToSoftObjectPath(),
		DisconnectedFriendsDataAsset.ToSoftObjectPath()
	};
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AssetsToLoad,
		FStreamableDelegate::CreateUObject(this, &UHUDContainerWidget::OnDataAssetsLoaded));
}

void UHUDContainerWidget::OnDataAssetsLoaded() const
{
	ConnectedFriends->SetVisibility(ESlateVisibility::Visible);
	DisconnectedFriends->SetVisibility(ESlateVisibility::Visible);
	ConnectedFriends->WidgetViewModelDataLoaded(ConnectedFriendsDataAsset.Get());
	DisconnectedFriends->WidgetViewModelDataLoaded(DisconnectedFriendsDataAsset.Get());
}
