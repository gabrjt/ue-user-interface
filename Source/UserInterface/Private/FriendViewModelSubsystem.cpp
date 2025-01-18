#include "FriendViewModelSubsystem.h"
#include "FriendListViewModel.h"
#include "FriendService.h"
#include "FriendServiceProviderSubsystem.h"

UFriendViewModelSubsystem::UFriendViewModelSubsystem()
	: ConnectedFriendsViewModel()
	, DisconnectedFriendsViewModel()
{
}

void UFriendViewModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ConnectedFriendsViewModel    = NewObject<UFriendListViewModel>();
	DisconnectedFriendsViewModel = NewObject<UFriendListViewModel>();

	IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	FriendService->SubscribeOnFriendsLoaded(FOnFriendsLoaded::CreateUObject(this, &UFriendViewModelSubsystem::OnFriendsLoaded));
	FriendService->SubscribeOnFriendUpdated(FOnFriendUpdated::CreateUObject(this, &UFriendViewModelSubsystem::OnFriendUpdated));
}

void UFriendViewModelSubsystem::Deinitialize()
{
	ConnectedFriendsViewModel->ClearFriends();
	DisconnectedFriendsViewModel->ClearFriends();

	if (IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() }; FriendService)
	{
		FriendService->UnsubscribeOnFriendsLoaded();
		FriendService->UnsubscribeOnFriendUpdated();
	}
}

UFriendListViewModel* UFriendViewModelSubsystem::GetConnectedFriendsViewModel() const
{
	return ConnectedFriendsViewModel;
}

UFriendListViewModel* UFriendViewModelSubsystem::GetDisconnectedFriendsViewModel() const
{
	return DisconnectedFriendsViewModel;
}

void UFriendViewModelSubsystem::OnFriendsLoaded() const
{
	const IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	ConnectedFriendsViewModel->SetFriendsFromData(FriendService->GetConnectedFriends_Implementation());
	DisconnectedFriendsViewModel->SetFriendsFromData(FriendService->GetDisconnectedFriends_Implementation());
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
