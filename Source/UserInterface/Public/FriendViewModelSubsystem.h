#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendViewModelSubsystem.generated.h"

class UFriendListViewModelBase;
class UConnectedFriendListViewModel;
struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModelBase* ConnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModelBase* DisconnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UConnectedFriendListViewModel* FriendsNotificationsViewModel;

public:
	UFriendViewModelSubsystem();

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// Public API
	UFriendListViewModelBase* GetConnectedFriendsViewModel() const;

	UFriendListViewModelBase* GetDisconnectedFriendsViewModel() const;

	UConnectedFriendListViewModel* GetFriendsNotificationsViewModel() const;

private:
	void OnFriendsLoaded() const;

	void OnFriendUpdated(const FFriendData& FriendData) const;
};
