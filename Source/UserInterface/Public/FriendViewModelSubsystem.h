#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendViewModelSubsystem.generated.h"

class UFriendListViewModel;
struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* ConnectedFriendsViewModel {};

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* DisconnectedFriendsViewModel {};

public:
	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	const UFriendListViewModel& GetConnectedFriendsViewModel() const;

	const UFriendListViewModel& GetDisconnectedFriendsViewModel() const;

private:
	void OnFriendsLoaded() const;

	void OnFriendUpdated(const FFriendData& FriendData) const;
};
