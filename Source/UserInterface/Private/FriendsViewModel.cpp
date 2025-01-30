#include "FriendsViewModel.h"
#include "FriendData.h"

UFriendsViewModel::UFriendsViewModel()
	: Friends()
	, OnFriendAdded()
{
}

UFriendsViewModel::~UFriendsViewModel()
{
	OnFriendAdded.Unbind();
}

void UFriendsViewModel::SetFriendsFromData(const TArray<FFriendData>& InFriends)
{
	Friends.Reset(InFriends.Num());

	for (auto& Friend : InFriends)
	{
		AddFriend(Friend);
	}

	BroadcastFriends();
}

void UFriendsViewModel::SetFriends(const TArray<UFriendViewModel*>& InFriends)
{
	Friends = InFriends;
}

const TArray<UFriendViewModel*>& UFriendsViewModel::GetFriends() const
{
	return Friends;
}

void UFriendsViewModel::RemoveFriend(const FString& UserID)
{
	if (const int32 Index {
		Friends.IndexOfByPredicate([&UserID](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == UserID;
		})
	}; Index != INDEX_NONE)
	{
		Friends.RemoveAt(Index);

		BroadcastFriends();
	}
}

void UFriendsViewModel::ClearFriends()
{
	Friends.Empty();

	BroadcastFriends();
}

void UFriendsViewModel::UpdateFriend(const FFriendData& InFriend)
{
	if (const int32 Index {
		Friends.IndexOfByPredicate([&InFriend](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == InFriend;
		})
	}; Index != INDEX_NONE)
	{
		Friends[Index]->Set(InFriend);
	}
	else
	{
		AddFriend(InFriend);
		BroadcastFriends();
		BroadcastGetLastAddedFriend();

		if (OnFriendAdded.IsBound())
		{
			OnFriendAdded.Execute(InFriend);
		}
	}
}

int UFriendsViewModel::GetFriendsCount() const
{
	return Friends.Num();
}

UFriendViewModel* UFriendsViewModel::GetLastAddedFriend() const
{
	if (Friends.IsEmpty())
	{
		return nullptr;
	}

	return Friends[Friends.Num() - 1];
}

void UFriendsViewModel::FriendAdded(int Index)
{
}

void UFriendsViewModel::BroadcastFriends()
{
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
}
