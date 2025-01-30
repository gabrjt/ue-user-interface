#include "FriendViewModelSubsystem.h"
#include "ConnectedFriendListViewModel.h"
#include "FriendListViewModelBase.h"
#include "FriendService.h"
#include "FriendServiceProviderSubsystem.h"

UFriendViewModelSubsystem::UFriendViewModelSubsystem()
	: ConnectedFriendsViewModel()
	, DisconnectedFriendsViewModel()
	, ConnectedFriendsNotificationsViewModel()
{
}

void UFriendViewModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ConnectedFriendsViewModel     = NewObject<UFriendListViewModelBase>();
	DisconnectedFriendsViewModel  = NewObject<UFriendListViewModelBase>();
	FriendsNotificationsViewModel = NewObject<UConnectedFriendListViewModel>();

	ConnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateUObject(ConnectedFriendsNotificationsViewModel,
		&UConnectedFriendListViewModel::OnFriendConnected);

	IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	FriendService->SubscribeOnFriendsLoaded(FOnFriendsLoaded::CreateUObject(this, &UFriendViewModelSubsystem::OnFriendsLoaded));
	FriendService->SubscribeOnFriendUpdated(FOnFriendUpdated::CreateUObject(this, &UFriendViewModelSubsystem::OnFriendUpdated));
}

void UFriendViewModelSubsystem::Deinitialize()
{
	ConnectedFriendsViewModel->ClearFriends();
	DisconnectedFriendsViewModel->ClearFriends();
	FriendsNotificationsViewModel->ClearFriends();

	if (IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() }; FriendService)
	{
		FriendService->UnsubscribeOnFriendsLoaded();
		FriendService->UnsubscribeOnFriendUpdated();
	}
}

UFriendListViewModelBase* UFriendViewModelSubsystem::GetConnectedFriendsViewModel() const
{
	return ConnectedFriendsViewModel;
}

UFriendListViewModelBase* UFriendViewModelSubsystem::GetDisconnectedFriendsViewModel() const
{
	return DisconnectedFriendsViewModel;
}

UConnectedFriendListViewModel* UFriendViewModelSubsystem::GetFriendsNotificationsViewModel() const
{
	return FriendsNotificationsViewModel;
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
