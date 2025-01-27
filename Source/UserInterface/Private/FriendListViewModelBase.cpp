#include "FriendListViewModelBase.h"
#include "FriendData.h"

UFriendListViewModelBase::UFriendListViewModelBase()
	: Friends()
{
}

void UFriendListViewModelBase::SetFriends(const TArray<UFriendViewModel*>& InFriends)
{
	Friends = InFriends;
}

const TArray<UFriendViewModel*>& UFriendListViewModelBase::GetFriends() const
{
	return Friends;
}

void UFriendListViewModelBase::RemoveFriend(const FString& UserID)
{
	if (const int32 Index{
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

void UFriendListViewModelBase::ClearFriends()
{
	Friends.Empty();

	BroadcastFriends();
}

UFriendViewModel* UFriendListViewModelBase::UpdateFriend(const FFriendData& InFriend)
{
	UFriendViewModel* FriendViewModel;
	
	if (const int32 Index{
		Friends.IndexOfByPredicate([&InFriend](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == InFriend;
		})
	}; Index != INDEX_NONE)
	{
		FriendViewModel = Friends[Index];
		FriendViewModel->Set(InFriend);
	}
	else
	{
		FriendViewModel = Friends[AddFriend(InFriend)];

		BroadcastFriends();
		BroadcastGetLastAddedFriend();
	}

	return FriendViewModel;
}

int UFriendListViewModelBase::GetFriendsCount() const
{
	return Friends.Num();
}


UFriendViewModel* UFriendListViewModelBase::GetLastAddedFriend() const
{
	if (Friends.IsEmpty())
	{
		return nullptr;
	}

	return Friends[Friends.Num() - 1];
}

void UFriendListViewModelBase::OnFriendAdded(int Index)
{
}

void UFriendListViewModelBase::BroadcastFriends()
{
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
}
