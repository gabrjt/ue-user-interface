// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendConnectionService.h"
#include "FriendConnectionViewModel.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendConnectionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendStatusChangedDynamic, UFriendConnectionViewModel*, FriendData);

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendConnectionManager : public UGameInstanceSubsystem, public IFriendConnectionService
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FFriendConnectionData> Friends;

	FOnFriendStatusChanged OnFriendStatusChanged;

public:
	UPROPERTY(BlueprintAssignable, Category = "Friends")
	FOnFriendStatusChangedDynamic OnFriendStatusChangedBP;

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// IFriendConnectionService interface
	virtual TArray<FFriendConnectionData> GetConnectedFriends() const override;

	virtual TArray<FFriendConnectionData> GetDisconnectedFriends() const override;

	virtual FDelegateHandle RegisterForFriendStatusUpdates(const FOnFriendStatusChangedDelegate& Callback) override;

	virtual void UnregisterFromFriendStatusUpdates(FDelegateHandle Handle) override;

	// Public API
	void UpdateFriendStatus(const FFriendConnectionData& FriendData);

	void HandleOnlineStatusUpdate(const FString& UserID, bool bConnected);

	void AddFriend(const FFriendConnectionData& NewFriend);

	void RemoveFriend(const FString& UserID);
};
