#pragma once

#include "FriendService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendViewModelSubsystem.generated.h"

class UFriendListViewModel;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FDelegateHandle OnFriendUpdatedHandle {};

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* ConnectedFriendsViewModel {};

	UPROPERTY(Transient, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UFriendListViewModel* DisconnectedFriendsViewModel {};

public:
	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

private:
	void OnFriendUpdated(const FFriendData& FriendData) const;
};
