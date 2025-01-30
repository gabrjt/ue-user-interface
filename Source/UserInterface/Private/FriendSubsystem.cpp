#include "FriendSubsystem.h"
#include "FriendData.h"
#include "FriendServiceProviderSubsystem.h"
#include "FriendsViewModelSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"

UFriendSubsystem::UFriendSubsystem()
	: FriendsDataTablePath()
	, Friends()
	, OnFriendsLoaded()
	, OnFriendUpdated()
	, OnFriendUpdatedBP() {}

void UFriendSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(UFriendServiceProviderSubsystem::StaticClass());
	Collection.InitializeDependency(UFriendsViewModelSubsystem::StaticClass());
}

void UFriendSubsystem::Deinitialize()
{
	Friends.Empty();
	OnFriendsLoaded.Unbind();
	OnFriendUpdated.Unbind();
	OnFriendUpdatedBP.Clear();
}

void UFriendSubsystem::SubscribeOnFriendsLoaded(const FOnFriendsLoaded& Callback)
{
	OnFriendsLoaded = Callback;
}

void UFriendSubsystem::UnsubscribeOnFriendsLoaded()
{
	OnFriendsLoaded.Unbind();
}

void UFriendSubsystem::SubscribeOnFriendUpdated(const FOnFriendUpdated& Callback)
{
	OnFriendUpdated = Callback;
}

void UFriendSubsystem::UnsubscribeOnFriendUpdated()
{
	OnFriendUpdated.Unbind();
}

void UFriendSubsystem::LoadFriends_Implementation()
{
	LoadFriendsAsync();
}

bool UFriendSubsystem::GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const
{
	for (auto& Friend : Friends)
	{
		if (Friend == UserID)
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

const TArray<FFriendData>& UFriendSubsystem::GetFriendsRef() const
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

void UFriendSubsystem::UpdateFriend_Implementation(const FFriendData& InFriend)
{
	int32                         Index { Friends.IndexOfByKey(InFriend) };
	TFunction<void(FFriendData&)> UpdateFunction = [&InFriend](FFriendData& Friend)
	{
		Friend = InFriend;
	};

	if (Index == INDEX_NONE)
	{
		Index          = Friends.Add(InFriend);
		UpdateFunction = nullptr;
	}

	UpdateFriend(Index, UpdateFunction);
}

void UFriendSubsystem::SetFriendIsConnected_Implementation(const FString& UserID, bool bIsConnected)
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

void UFriendSubsystem::SetFriendLevel_Implementation(const FString& UserID, const int Level)
{
	if (const int32 Index { Friends.IndexOfByKey(UserID) }; Index != INDEX_NONE)
	{
		UpdateFriend(Index,
			[Level](FFriendData& Friend)
			{
				Friend.Level = Level;
			});
	}
}

void UFriendSubsystem::RemoveFriend_Implementation(const FString& UserID)
{
	if (const int32 Index { Friends.IndexOfByKey(UserID) }; Index != INDEX_NONE)
	{
		Friends.RemoveAtSwap(Index);
	}
}

TSharedPtr<FStreamableHandle> UFriendSubsystem::LoadFriendsAsync()
{
	if (!FriendsDataTablePath.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Friends DataTable path: %s"), *FriendsDataTablePath.ToString());

		return {};
	}

	FStreamableManager& StreamableManager { UAssetManager::GetStreamableManager() };
	return StreamableManager.RequestAsyncLoad(FriendsDataTablePath,
		FStreamableDelegate::CreateUObject(this, &UFriendSubsystem::OnFriendsDataTableLoaded));
}

void UFriendSubsystem::LoadFriends(const UDataTable* DataTable)
{
	if (!IsValid(DataTable))
	{
		return;
	}

	const TArray<FName>& RowNames { DataTable->GetRowNames() };

	Friends.Reset(RowNames.Num());

	for (const FName& RowName : RowNames)
	{
		if (const FFriendData* FriendData { DataTable->FindRow<FFriendData>(RowName, TEXT("")) })
		{
			Friends.Add(*FriendData);
		}
	}

	if (OnFriendsLoaded.IsBound())
	{
		OnFriendsLoaded.Execute();
	}
}

void UFriendSubsystem::OnFriendsDataTableLoaded()
{
	const UDataTable* DataTable { Cast<UDataTable>(FriendsDataTablePath.ResolveObject()) };

	LoadFriends(DataTable);
}

void UFriendSubsystem::UpdateFriend(const int32 Index, const TFunction<void(FFriendData&)>& UpdateFunction)
{
	check(Index != INDEX_NONE && Index >= 0 && Index < Friends.Num());

	FFriendData& Friend { Friends[Index] };

	if (UpdateFunction)
	{
		UpdateFunction(Friend);
	}

	if (OnFriendUpdated.IsBound())
	{
		OnFriendUpdated.Execute(Friend);
	}

	OnFriendUpdatedBP.Broadcast(Friend);
}
