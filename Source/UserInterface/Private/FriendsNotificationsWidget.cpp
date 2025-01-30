#include "FriendsNotificationsWidget.h"
#include "FriendsViewModel.h"
#include "FriendsViewModelType.h"

void UFriendsNotificationsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	const EFriendsViewModelType ViewModelFlags { static_cast<EFriendsViewModelType>(ViewModelType) };

	if (UFriendsViewModel* ConnectedFriendsViewModel { GetViewModel(ConnectedFriendsViewModelName) };
		ConnectedFriendsViewModel && EnumHasAnyFlags(ViewModelFlags, EFriendsViewModelType::Connected))
	{
		ConnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateLambda([this](const FFriendData& FriendData)
		{
			GetViewModel()->AddFriend(FriendData);
		});
	}

	if (UFriendsViewModel* DisconnectedFriendsViewModel { GetViewModel(DisconnectedFriendsViewModelName) };
		DisconnectedFriendsViewModel && EnumHasAnyFlags(ViewModelFlags, EFriendsViewModelType::Disconnected))
	{
		DisconnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateLambda([this](const FFriendData& FriendData)
		{
			GetViewModel()->AddFriend(FriendData);
		});
	}
}
