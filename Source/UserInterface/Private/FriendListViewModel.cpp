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
	for (auto& Friend : InFriends)
	{
		UpdateFriend(Friend);
	}
}

void UFriendListViewModel::AddFriend(UFriendViewModel* Friend)
{
	if (Friend)
	{
		Friends.Add(Friend);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
	}
}

void UFriendListViewModel::RemoveFriend(const FString& UserID)
{
	Friends.RemoveAll([UserID](const UFriendViewModel* Friend)
	{
		return Friend && Friend->GetUserID() == UserID;
	});
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
}

void UFriendListViewModel::ClearFriends()
{
	Friends.Empty();
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
}

void UFriendListViewModel::UpdateFriend(const FFriendData& FriendData)
{
	// Try to find existing friend
	UFriendViewModel* ExistingFriend = nullptr;
	for (UFriendViewModel* Friend : Friends)
	{
		if (Friend && Friend->GetUserID() == FriendData.UserID)
		{
			ExistingFriend = Friend;
			break;
		}
	}

	if (ExistingFriend)
	{
		// Update existing friend
		ExistingFriend->Set(FriendData);
	}
	else
	{
		// Create and add new friend
		UFriendViewModel* NewFriend = NewObject<UFriendViewModel>(this);
		NewFriend->Set(FriendData);
		AddFriend(NewFriend);
	}
}
