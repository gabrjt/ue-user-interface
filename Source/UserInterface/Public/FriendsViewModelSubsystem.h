#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendsViewModelSubsystem.generated.h"

class UFriendsViewModel;
class UConnectedFriendListViewModel;
struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendsViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendsViewModel* ConnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendsViewModel* DisconnectedFriendsViewModel;

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UConnectedFriendListViewModel* FriendsNotificationsViewModel;

public:
	UFriendsViewModelSubsystem();

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// Public API
	UFriendsViewModel* GetConnectedFriendsViewModel() const;

	UFriendsViewModel* GetDisconnectedFriendsViewModel() const;

	UConnectedFriendListViewModel* GetFriendsNotificationsViewModel() const;

private:
	void OnFriendsLoaded() const;

	void OnFriendUpdated(const FFriendData& FriendData) const;
};
