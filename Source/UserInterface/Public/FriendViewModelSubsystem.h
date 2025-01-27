#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendViewModelSubsystem.generated.h"

class UFriendListViewModel;
class UConnectedFriendListViewModel;
struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* ConnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* DisconnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UConnectedFriendListViewModel* ConnectedFriendsNotificationsViewModel;

public:
	UFriendViewModelSubsystem();

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// Public API
	UFriendListViewModel* GetConnectedFriendsViewModel() const;

	UFriendListViewModel* GetDisconnectedFriendsViewModel() const;

	UConnectedFriendListViewModel* GetConnectedFriendsNotificationsViewModel() const;

private:
	void OnFriendsLoaded() const;

	void OnFriendUpdated(const FFriendData& FriendData) const;
};
