#include "FriendsViewModelSubsystem.h"
#include "FriendsViewModel.h"
#include "FriendService.h"
#include "FriendServiceProviderSubsystem.h"

UFriendsViewModelSubsystem::UFriendsViewModelSubsystem()
	: ConnectedFriendsViewModel()
	, DisconnectedFriendsViewModel()
	, FriendsNotificationsViewModel()
{
}

void UFriendsViewModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ConnectedFriendsViewModel     = NewObject<UFriendsViewModel>();
	DisconnectedFriendsViewModel  = NewObject<UFriendsViewModel>();
	FriendsNotificationsViewModel = NewObject<UFriendsViewModel>();

	ConnectedFriendsViewModel->OnFriendAdded = FOnFriendAdded::CreateLambda([this](const FFriendData& FriendData)
	{
		FriendsNotificationsViewModel->AddFriend(FriendData);
	});

	IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	FriendService->SubscribeOnFriendsLoaded(FOnFriendsLoaded::CreateUObject(this, &UFriendsViewModelSubsystem::OnFriendsLoaded));
	FriendService->SubscribeOnFriendUpdated(FOnFriendUpdated::CreateUObject(this, &UFriendsViewModelSubsystem::OnFriendUpdated));
}

void UFriendsViewModelSubsystem::Deinitialize()
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

UFriendsViewModel* UFriendsViewModelSubsystem::GetConnectedFriendsViewModel() const
{
	return ConnectedFriendsViewModel;
}

UFriendsViewModel* UFriendsViewModelSubsystem::GetDisconnectedFriendsViewModel() const
{
	return DisconnectedFriendsViewModel;
}

UFriendsViewModel* UFriendsViewModelSubsystem::GetFriendsNotificationsViewModel() const
{
	return FriendsNotificationsViewModel;
}

void UFriendsViewModelSubsystem::OnFriendsLoaded() const
{
	const IFriendService* FriendService { GetGameInstance()->GetSubsystem<UFriendServiceProviderSubsystem>()->GetFriendServiceInterface() };

	ConnectedFriendsViewModel->SetFriendsFromData(FriendService->GetConnectedFriends_Implementation());
	DisconnectedFriendsViewModel->SetFriendsFromData(FriendService->GetDisconnectedFriends_Implementation());
}

void UFriendsViewModelSubsystem::OnFriendUpdated(const FFriendData& FriendData) const
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
