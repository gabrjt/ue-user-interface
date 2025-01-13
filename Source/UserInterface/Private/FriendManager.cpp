// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendManager.h"
#include "FriendData.h"

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

void UFriendManager::UnsubscribeOnFriendUpdated(FDelegateHandle Handle)
{
	OnFriendUpdated.Remove(Handle);
}

void UFriendManager::UpdateFriend(const FFriendData& InFriend)
{
	// Find and update existing friend or add new one
	bool bFound = false;

	for (auto& Friend : Friends)
	{
		if (Friend.UserID == InFriend.UserID)
		{
			Friend = InFriend;
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		Friends.Add(InFriend);
	}

	OnFriendUpdated.Broadcast(InFriend);
	OnFriendUpdatedBP.Broadcast(InFriend);
}

void UFriendManager::SetFriendIsConnected(const FString& UserID, bool bIsConnected)
{
	for (const auto& Friend : Friends)
	{
		if (Friend.UserID == UserID)
		{
			FFriendData UpdatedData  = Friend;
			UpdatedData.bIsConnected = bIsConnected;
			UpdatedData.LastSeen     = bIsConnected ? TEXT("Online Now") : FDateTime::Now().ToString();
			UpdateFriend(UpdatedData);
			break;
		}
	}
}

void UFriendManager::AddFriend(const FFriendData& InFriend)
{
	UpdateFriend(InFriend);
}

void UFriendManager::RemoveFriend(const FString& UserID)
{
	Friends.RemoveAll([UserID](const FFriendData& Friend)
	{
		return Friend.UserID == UserID;
	});
}
