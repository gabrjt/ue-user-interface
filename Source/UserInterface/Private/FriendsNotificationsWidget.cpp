#include "FriendsNotificationsWidget.h"
#include "FriendsNotificationsWidgetEntry.h"
#include "FriendsNotificationsWidgetEntryViewModelDataAsset.h"
#include "FriendsViewModel.h"
#include "FriendsViewModelType.h"
#include "Components/ListView.h"
#include "Engine/AssetManager.h"

void UFriendsNotificationsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnEntryWidgetGeneratedHandle = FriendListView->OnEntryWidgetGenerated().AddUObject(this,
		&UFriendsNotificationsWidget::OnEntryWidgetGenerated);
}

void UFriendsNotificationsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	const EFriendsViewModelType ViewModelFlags { static_cast<EFriendsViewModelType>(ViewModelType) };

	if (UFriendsViewModel* ConnectedFriendsViewModel { GetViewModel(ConnectedFriendsViewModelName) };
		ConnectedFriendsViewModel && EnumHasAnyFlags(ViewModelFlags, EFriendsViewModelType::Connected))
	{
		ConnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateUObject(this,
			&UFriendsNotificationsWidget::OnFriendAdded);
	}

	if (UFriendsViewModel* DisconnectedFriendsViewModel { GetViewModel(DisconnectedFriendsViewModelName) };
		DisconnectedFriendsViewModel && EnumHasAnyFlags(ViewModelFlags, EFriendsViewModelType::Disconnected))
	{
		DisconnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateUObject(this,
			&UFriendsNotificationsWidget::OnFriendAdded);
	}
}

void UFriendsNotificationsWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (FriendListView && OnEntryWidgetGeneratedHandle.IsValid())
	{
		FriendListView->OnEntryWidgetGenerated().Remove(OnEntryWidgetGeneratedHandle);
		OnEntryWidgetGeneratedHandle.Reset();
	}
}

void UFriendsNotificationsWidget::OnFriendAdded(const FFriendData& FriendData) const
{
	GetViewModel()->AddFriend(FriendData);
}

void UFriendsNotificationsWidget::OnEntryWidgetGenerated(UUserWidget& UserWidget) const
{
	UFriendsNotificationsWidgetEntry* WidgetEntry { Cast<UFriendsNotificationsWidgetEntry>(&UserWidget) };
	const TSoftObjectPtr<UFriendsNotificationsWidgetEntryViewModelDataAsset> DataAsset {
		WidgetEntry->GetIsConnected() ? ConnectedNotificationDataAsset : DisconnectedNotificationDataAsset
	};

	FStreamableManager& StreamableManager { UAssetManager::GetStreamableManager() };
	StreamableManager.RequestAsyncLoad(DataAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([=]
		{
			WidgetEntry->WidgetViewModelDataLoaded(DataAsset.Get());
		}));
}
