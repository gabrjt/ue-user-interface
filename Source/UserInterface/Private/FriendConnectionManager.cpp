// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendConnectionManager.h"
#include "FriendConnectionData.h"

void UFriendConnectionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFriendConnectionManager::Deinitialize()
{
	Friends.Empty();
	OnFriendStatusChanged.Clear();
	OnFriendStatusChangedBP.Clear();
	Super::Deinitialize();
}

TArray<FFriendConnectionData> UFriendConnectionManager::GetConnectedFriends() const
{
	return Friends.FilterByPredicate([](const FFriendConnectionData& Friend)
	{
		return Friend.bIsConnected;
	});
}

TArray<FFriendConnectionData> UFriendConnectionManager::GetDisconnectedFriends() const
{
	return Friends.FilterByPredicate([](const FFriendConnectionData& Friend)
	{
		return !Friend.bIsConnected;
	});
}

FDelegateHandle UFriendConnectionManager::RegisterForFriendStatusUpdates(const FOnFriendStatusChangedDelegate& Callback)
{
	return OnFriendStatusChanged.Add(Callback);
}

void UFriendConnectionManager::UnregisterFromFriendStatusUpdates(FDelegateHandle Handle)
{
	OnFriendStatusChanged.Remove(Handle);
}

void UFriendConnectionManager::UpdateFriendStatus(const FFriendConnectionData& FriendData)
{
	// Find and update existing friend or add new one
	bool bFound = false;
	for (auto& Friend : Friends)
	{
		if (Friend.UserID == FriendData.UserID)
		{
			Friend = FriendData;
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		Friends.Add(FriendData);
	}

	OnFriendStatusChanged.Broadcast(FriendData);
	OnFriendStatusChangedBP.Broadcast(FriendData);
}

void UFriendConnectionManager::HandleOnlineStatusUpdate(const FString& UserID, bool bConnected)
{
	for (const auto& Friend : Friends)
	{
		if (Friend.UserID == UserID)
		{
			FFriendConnectionData UpdatedData = Friend;
			UpdatedData.bIsConnected          = bConnected;
			UpdatedData.LastSeen              = bConnected ? TEXT("Online Now") : FDateTime::Now().ToString();
			UpdateFriendStatus(UpdatedData);
			break;
		}
	}
}

void UFriendConnectionManager::AddFriend(const FFriendConnectionData& NewFriend)
{
	UpdateFriendStatus(NewFriend);
}

void UFriendConnectionManager::RemoveFriend(const FString& UserID)
{
	Friends.RemoveAll([UserID](const FFriendConnectionData& Friend)
	{
		return Friend.UserID == UserID;
	});
}
