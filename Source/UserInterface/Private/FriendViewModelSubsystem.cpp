#include "FriendViewModelSubsystem.h"
#include "FriendListViewModel.h"
#include "FriendService.h"
#include "FriendServiceProviderSubsystem.h"

void UFriendViewModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ConnectedFriendsViewModel    = NewObject<UFriendListViewModel>();
	DisconnectedFriendsViewModel = NewObject<UFriendListViewModel>();

	IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	// TODO: load friends event for batch initialization
	OnFriendUpdatedHandle = FriendService->SubscribeOnFriendUpdated(FOnFriendUpdatedDelegate::CreateUObject(this, &UFriendViewModelSubsystem::OnFriendUpdated));
}

void UFriendViewModelSubsystem::Deinitialize()
{
	ConnectedFriendsViewModel->ClearFriends();
	DisconnectedFriendsViewModel->ClearFriends();

	if (IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() }; FriendService)
	{
		FriendService->UnsubscribeOnFriendUpdated(OnFriendUpdatedHandle);
	}

	OnFriendUpdatedHandle.Reset();
}

void UFriendViewModelSubsystem::OnFriendUpdated(const FFriendData& FriendData) const
{
	if (FriendData.bIsConnected)
	{
		ConnectedFriendsViewModel->UpdateFriend(FriendData);
		DisconnectedFriendsViewModel->RemoveFriend(FriendData.UserID);
	}
	else
	{
		ConnectedFriendsViewModel->RemoveFriend(FriendData.UserID);
		DisconnectedFriendsViewModel->UpdateFriend(FriendData);
	}
}
