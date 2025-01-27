#include "ConnectedFriendListViewModel.h"

UConnectedFriendListViewModel::UConnectedFriendListViewModel()
	: UFriendListViewModelBase()
{
}

void UConnectedFriendListViewModel::OnFriendConnected(const FFriendData& FriendData)
{
	AddFriend(FriendData);
}

void UConnectedFriendListViewModel::FriendAdded(const int Index)
{
	Super::BroadcastFriends();
	BroadcastGetLastAddedFriend();
}
