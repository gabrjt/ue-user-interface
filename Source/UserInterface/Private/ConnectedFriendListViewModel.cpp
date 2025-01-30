#include "ConnectedFriendListViewModel.h"

UConnectedFriendListViewModel::UConnectedFriendListViewModel()
	: UFriendsViewModel()
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
