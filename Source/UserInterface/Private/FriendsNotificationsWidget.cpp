#include "FriendsNotificationsWidget.h"
#include "FriendsViewModel.h"

void UFriendsNotificationsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	GetViewModel(ConnectedFriendsViewModelName)->OnFriendAdded = FOnFriendAdded::CreateLambda(
		[this](const FFriendData& FriendData)
		{
			GetViewModel()->AddFriend(FriendData);
		});
}
