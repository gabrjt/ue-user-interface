#include "FriendViewModel.h"
#include "ConnectedFriendListViewModel.h"

UConnectedFriendListViewModel::UConnectedFriendListViewModel()
	: UFriendListViewModelBase()
{
}

/*UFriendViewModel* UConnectedFriendListViewModel::AddFriend(UFriendViewModel* InFriend)
{
	UFriendViewModel* Friend { Super::AddFriend(InFriend) };

	Super::BroadcastFriends();

	return Friend;
}

void UConnectedFriendListViewModel::BroadcastFriends()
{
	Super::BroadcastFriends();
	BroadcastFriendAdded();
}*/
