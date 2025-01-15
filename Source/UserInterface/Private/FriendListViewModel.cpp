#include "FriendListViewModel.h"
#include "FriendData.h"
#include "FriendViewModel.h"

UFriendListViewModel::UFriendListViewModel()
{
}

const TArray<UFriendViewModel*>& UFriendListViewModel::GetFriends() const
{
	return Friends;
}

void UFriendListViewModel::SetFriends(const TArray<FFriendData>& InFriends)
{
	Friends.Reset(InFriends.Num());

	for (auto& Friend : InFriends)
	{
		AddFriend(Friend);
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
}

void UFriendListViewModel::RemoveFriend(const FString& UserID)
{
	if (const int32 Index = Friends.IndexOfByPredicate([&UserID](const UFriendViewModel* Friend)
	{
		return Friend && *Friend == UserID;
	}); Index != INDEX_NONE)
	{
		Friends.RemoveAtSwap(Index);

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
	}
}

void UFriendListViewModel::ClearFriends()
{
	Friends.Empty();

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
}

void UFriendListViewModel::UpdateFriend(const FFriendData& InFriend)
{
	if (const int32 Index = Friends.IndexOfByPredicate([&InFriend](const UFriendViewModel* Friend)
	{
		return Friend && *Friend == InFriend;
	}); Index != INDEX_NONE)
	{
		Friends[Index]->Set(InFriend);
	}
	else
	{
		AddFriend(InFriend);

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
	}
}

void UFriendListViewModel::SetTitle(const FString& InTitle)
{
	UE_MVVM_SET_PROPERTY_VALUE(Title, InTitle);
}

const FString& UFriendListViewModel::GetTitle() const
{
	return Title;
}

int UFriendListViewModel::GetFriendsCount() const
{
	return Friends.Num();
}
