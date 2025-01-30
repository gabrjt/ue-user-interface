#include "FriendsViewModel.h"
#include "FriendData.h"
#include "FriendService.h"
#include "FriendServiceProviderSubsystem.h"
#include "FriendsViewModelType.h"
#include "Kismet/GameplayStatics.h"

UFriendsViewModel::UFriendsViewModel()
	: Type()
	, Friends()
	, OnFriendsLoadedHandle()
	, OnFriendUpdatedHandle()
	, OnFriendAdded() {}

void UFriendsViewModel::BeginDestroy()
{
	Super::BeginDestroy();

	ClearFriends();

	if (const UGameInstance* GameInstance { UGameplayStatics::GetGameInstance(this) })
	{
		IFriendService* FriendService {
			GameInstance->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface()
		};

		FriendService->UnsubscribeOnFriendsLoaded(OnFriendsLoadedHandle);
		FriendService->UnsubscribeOnFriendUpdated(OnFriendUpdatedHandle);
	}

	OnFriendsLoadedHandle.Reset();
	OnFriendUpdatedHandle.Reset();
	OnFriendAdded.Unbind();
}

void UFriendsViewModel::SetFriendsFromData(const TArray<FFriendData>& InFriends)
{
	Friends.Reset(InFriends.Num());

	for (auto& Friend : InFriends)
	{
		AddFriend_Internal(Friend);
	}

	BroadcastFriends();
}

void UFriendsViewModel::SetFriends(const TArray<UFriendViewModel*>& InFriends)
{
	Friends = InFriends;
}

const TArray<UFriendViewModel*>& UFriendsViewModel::GetFriends() const
{
	return Friends;
}

void UFriendsViewModel::RemoveFriend(const FString& UserID)
{
	if (const int32 Index {
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

void UFriendsViewModel::ClearFriends()
{
	Friends.Empty();

	BroadcastFriends();
}

void UFriendsViewModel::UpdateFriend(const FFriendData& InFriend)
{
	if (const int32 Index {
		Friends.IndexOfByPredicate([&InFriend](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == InFriend;
		})
	}; Index != INDEX_NONE)
	{
		Friends[Index]->Set(InFriend);
	}
	else
	{
		AddFriend(InFriend);
	}
}

int UFriendsViewModel::GetFriendsCount() const
{
	return Friends.Num();
}

UFriendViewModel* UFriendsViewModel::GetLastAddedFriend() const
{
	if (Friends.IsEmpty())
	{
		return nullptr;
	}

	return Friends[Friends.Num() - 1];
}

void UFriendsViewModel::AddFriend(const FFriendData& InFriend)
{
	AddFriend_Internal(InFriend);
	BroadcastFriends();
	BroadcastGetLastAddedFriend();

	if (OnFriendAdded.IsBound())
	{
		OnFriendAdded.Execute(InFriend);
	}
}

void UFriendsViewModel::SubscribeFriendsService(const EFriendsViewModelType InType)
{
	Type = InType;

	IFriendService* FriendService {
		UGameplayStatics::GetGameInstance(this)->GetSubsystem<UFriendServiceProviderSubsystem>()->
		                                         GetFriendServiceInterface()
	};

	OnFriendsLoadedHandle = FriendService->SubscribeOnFriendsLoaded(
		FOnFriendsLoadedDelegate::CreateUObject(this, &UFriendsViewModel::OnFriendsLoaded));

	OnFriendUpdatedHandle = FriendService->SubscribeOnFriendUpdated(
		FOnFriendUpdatedDelegate::CreateUObject(this, &UFriendsViewModel::OnFriendUpdated));
}

TArray<FFriendData> UFriendsViewModel::GetFriendsData() const
{
	const IFriendService* FriendService {
		UGameplayStatics::GetGameInstance(this)->GetSubsystem<UFriendServiceProviderSubsystem>()->
		                                         GetFriendServiceInterface()
	};

	if (EnumHasAllFlags(Type, EFriendsViewModelType::Connected | EFriendsViewModelType::Disconnected))
	{
		return FriendService->GetFriendsRef();
	}

	if (EnumHasAnyFlags(Type, EFriendsViewModelType::Connected))
	{
		return FriendService->GetConnectedFriends_Implementation();
	}

	if (EnumHasAnyFlags(Type, EFriendsViewModelType::Disconnected))
	{
		return FriendService->GetDisconnectedFriends_Implementation();
	}

	return TArray<FFriendData>();
}

void UFriendsViewModel::OnFriendsLoaded()
{
	SetFriendsFromData(GetFriendsData());
}

void UFriendsViewModel::OnFriendUpdated(const FFriendData& FriendData)
{
	if (EnumHasAllFlags(Type, EFriendsViewModelType::Connected | EFriendsViewModelType::Disconnected))
	{
		UpdateFriend(FriendData);
	}
	else if (EnumHasAnyFlags(Type, EFriendsViewModelType::Connected))
	{
		if (FriendData.bIsConnected)
		{
			UpdateFriend(FriendData);
		}
		else
		{
			RemoveFriend(FriendData.UserID);
		}
	}
	else if (EnumHasAnyFlags(Type, EFriendsViewModelType::Disconnected))
	{
		if (!FriendData.bIsConnected)
		{
			UpdateFriend(FriendData);
		}
		else
		{
			RemoveFriend(FriendData.UserID);
		}
	}
}
