// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendSubsystem.h"
#include "FriendData.h"
#include "Engine/DataTable.h"

void UFriendSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFriendSubsystem::Deinitialize()
{
	Friends.Empty();
	OnFriendUpdated.Clear();
	OnFriendUpdatedBP.Clear();
	Super::Deinitialize();
}

bool UFriendSubsystem::GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const
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

TArray<FFriendData> UFriendSubsystem::GetFriends_Implementation() const
{
	return Friends;
}

TArray<FFriendData> UFriendSubsystem::GetConnectedFriends_Implementation() const
{
	return Friends.FilterByPredicate([](const FFriendData& Friend)
	{
		return Friend.bIsConnected;
	});
}

TArray<FFriendData> UFriendSubsystem::GetDisconnectedFriends_Implementation() const
{
	return Friends.FilterByPredicate([](const FFriendData& Friend)
	{
		return !Friend.bIsConnected;
	});
}

FDelegateHandle UFriendSubsystem::SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback)
{
	return OnFriendUpdated.Add(Callback);
}

void UFriendSubsystem::UnsubscribeOnFriendUpdated(const FDelegateHandle Handle)
{
	OnFriendUpdated.Remove(Handle);
}

void UFriendSubsystem::UpdateFriend(const FFriendData& InFriend)
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

void UFriendSubsystem::SetFriendIsConnected(const FString& UserID, bool bIsConnected)
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

void UFriendSubsystem::AddFriend(const FFriendData& InFriend)
{
	UpdateFriend(InFriend);
}

void UFriendSubsystem::RemoveFriend(const FString& UserID)
{
	if (const int32 Index { Friends.IndexOfByKey(UserID) }; Index != INDEX_NONE)
	{
		Friends.RemoveAtSwap(Index);
	}
}

void UFriendSubsystem::LoadFriends(const UDataTable* FriendsDataTable)
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

void UFriendSubsystem::UpdateFriend(const int32 Index, const TFunction<void(FFriendData&)>& UpdateFunction)
{
	ensure(Index != INDEX_NONE && Index >= 0 && Index < Friends.Num());

	FFriendData& Friend = Friends[Index];

	UpdateFunction(Friend);

	OnFriendUpdated.Broadcast(Friend);
	OnFriendUpdatedBP.Broadcast(Friend);
}
