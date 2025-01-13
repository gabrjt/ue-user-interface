// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendManager.generated.h"

struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendManager : public UGameInstanceSubsystem, public IFriendService
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TArray<FFriendData> Friends {};

	FOnFriendUpdated OnFriendUpdated {};

public:
	UPROPERTY(BlueprintAssignable, Category = "Friends")
	FOnFriendUpdatedDelegateDynamic OnFriendUpdatedBP {};

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// IFriendConnectionService interface
	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual TArray<FFriendData> GetConnectedFriends() const override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual TArray<FFriendData> GetDisconnectedFriends() const override;

	virtual FDelegateHandle SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback) override;

	virtual void UnsubscribeOnFriendUpdated(FDelegateHandle Handle) override;

	// Public API
	void UpdateFriend(const FFriendData& InFriend);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void SetFriendIsConnected(const FString& UserID, bool bIsConnected);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void AddFriend(const FFriendData& InFriend);

	UFUNCTION(BlueprintCallable, Category = "Friends")
	void RemoveFriend(const FString& UserID);
};
