// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendConnectionService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendConnectionManager.generated.h"

struct FFriendConnectionData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendConnectionManager : public UGameInstanceSubsystem, public IFriendConnectionService
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TArray<FFriendConnectionData> Friends {};

	FOnFriendStatusChanged OnFriendStatusChanged {};

public:
	UPROPERTY(BlueprintAssignable, Category = "Friends")
	FOnFriendStatusChangedDynamic OnFriendStatusChangedBP {};

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// IFriendConnectionService interface
	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual TArray<FFriendConnectionData> GetConnectedFriends() const override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual TArray<FFriendConnectionData> GetDisconnectedFriends() const override;

	virtual FDelegateHandle RegisterForFriendStatusUpdates(const FOnFriendStatusChangedDelegate& Callback) override;

	virtual void UnregisterFromFriendStatusUpdates(FDelegateHandle Handle) override;

	// Public API
	void UpdateFriendStatus(const FFriendConnectionData& FriendData);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void HandleOnlineStatusUpdate(const FString& UserID, bool bConnected);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void AddFriend(const FFriendConnectionData& NewFriend);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void RemoveFriend(const FString& UserID);
};
