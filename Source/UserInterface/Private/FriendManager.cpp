// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendManager.h"
#include "FriendData.h"
#include "Engine/DataTable.h"

void UFriendManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFriendManager::Deinitialize()
{
	Friends.Empty();
	OnFriendUpdated.Clear();
	OnFriendUpdatedBP.Clear();
	Super::Deinitialize();
}

bool UFriendManager::GetFriend(const FString& UserID, FFriendData& OutFriend) const
{
	for (auto& Friend : Friends)
	{
		if (Friend.UserID == UserID)
		{
			OutFriend = Friend;

			return true;
		}
	}

	return false;
}

const TArray<FFriendData>& UFriendManager::GetFriends() const
{
	return Friends;
}

TArray<FFriendData> UFriendManager::GetConnectedFriends() const
{
	return Friends.FilterByPredicate([](const FFriendData& Friend)
	{
		return Friend.bIsConnected;
	});
}

TArray<FFriendData> UFriendManager::GetDisconnectedFriends() const
{
	return Friends.FilterByPredicate([](const FFriendData& Friend)
	{
		return !Friend.bIsConnected;
	});
}

FDelegateHandle UFriendManager::SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback)
{
	return OnFriendUpdated.Add(Callback);
}

void UFriendManager::UnsubscribeOnFriendUpdated(const FDelegateHandle Handle)
{
	OnFriendUpdated.Remove(Handle);
}

void UFriendManager::UpdateFriend(const FFriendData& InFriend)
{
	int32 Index { Friends.IndexOfByKey(InFriend) };

	if (Index == INDEX_NONE)
	{
		Index = Friends.Add(InFriend);
	}

	UpdateFriend(Index,
		[&InFriend](FFriendData& Friend)
		{
			Friend = InFriend;
		});
}

void UFriendManager::SetFriendIsConnected(const FString& UserID, bool bIsConnected)
{
	if (const int32 Index { Friends.IndexOfByKey(UserID) }; Index != INDEX_NONE)
	{
		UpdateFriend(Index,
			[bIsConnected](FFriendData& Friend)
			{
				Friend.bIsConnected = bIsConnected;
				Friend.LastSeen     = FFriendData::GetLastSeen(bIsConnected);
			});
	}
}

void UFriendManager::AddFriend(const FFriendData& InFriend)
{
	UpdateFriend(InFriend);
}

void UFriendManager::RemoveFriend(const FString& UserID)
{
	if (const int32 Index { Friends.IndexOfByKey(UserID) }; Index != INDEX_NONE)
	{
		Friends.RemoveAtSwap(Index);
	}
}

void UFriendManager::LoadFriends(const UDataTable* FriendsDataTable)
{
	if (!IsValid(FriendsDataTable))
	{
		return;
	}

	for (const TArray<FName>& RowNames = FriendsDataTable->GetRowNames(); const FName& RowName : RowNames)
	{
		if (const FFriendData* FriendData = FriendsDataTable->FindRow<FFriendData>(RowName, TEXT("")))
		{
			UpdateFriend(*FriendData);
		}
	}
}

void UFriendManager::UpdateFriend(const int32 Index, const TFunction<void(FFriendData&)>& UpdateFunction)
{
	ensure(Index != INDEX_NONE && Index >= 0 && Index < Friends.Num());

	FFriendData& Friend = Friends[Index];

	UpdateFunction(Friend);

	OnFriendUpdated.Broadcast(Friend);
	OnFriendUpdatedBP.Broadcast(Friend);
}
