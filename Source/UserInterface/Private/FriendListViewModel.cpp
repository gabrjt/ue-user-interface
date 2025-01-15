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

	BroadcastFriends();
}

void UFriendListViewModel::RemoveFriend(const FString& UserID)
{
	if (const int32 Index = Friends.IndexOfByPredicate([&UserID](const UFriendViewModel* Friend)
	{
		return Friend && *Friend == UserID;
	}); Index != INDEX_NONE)
	{
		Friends.RemoveAtSwap(Index);

		BroadcastFriends();
	}
}

void UFriendListViewModel::ClearFriends()
{
	Friends.Empty();

	BroadcastFriends();
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
		BroadcastFriends();
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

void UFriendListViewModel::SetTextColor(const FSlateColor& InTextColor)
{
	UE_MVVM_SET_PROPERTY_VALUE(TextColor, InTextColor);
}

const FSlateColor& UFriendListViewModel::GetTextColor() const
{
	return TextColor;
}

int UFriendListViewModel::GetFriendsCount() const
{
	return Friends.Num();
}
