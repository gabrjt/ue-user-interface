#include "ConnectedFriendListViewModel.h"

UConnectedFriendListViewModel::UConnectedFriendListViewModel()
	: UFriendListViewModelBase()
{
}

void UConnectedFriendListViewModel::OnFriendAdded(int Index)
{
	Super::BroadcastFriends();
	BroadcastGetLastAddedFriend();
}
