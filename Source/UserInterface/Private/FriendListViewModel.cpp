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
		Friends.Add(UFriendViewModel::Create(this, Friend));
	}

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
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

void UFriendListViewModel::UpdateFriend(const FFriendData& InFriend)
{
	// Try to find existing friend
	UFriendViewModel* ExistingFriend = nullptr;

	for (UFriendViewModel* Friend : Friends)
	{
		if (Friend && Friend->GetUserID() == InFriend.UserID)
		{
			ExistingFriend = Friend;
			break;
		}
	}

	if (ExistingFriend)
	{
		// Update existing friend
		ExistingFriend->Set(InFriend);
	}
	else
	{
		// Create and add new friend
		AddFriend(UFriendViewModel::Create(this, InFriend));
	}
}
