// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendSubsystem.generated.h"

struct FFriendData;
class UDataTable;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendSubsystem : public UGameInstanceSubsystem, public IFriendService
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
	virtual bool GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const override;

	virtual TArray<FFriendData> GetFriends_Implementation() const override;

	virtual TArray<FFriendData> GetConnectedFriends_Implementation() const override;

	virtual TArray<FFriendData> GetDisconnectedFriends_Implementation() const override;

	virtual FDelegateHandle SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback) override;

	virtual void UnsubscribeOnFriendUpdated(const FDelegateHandle Handle) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void UpdateFriend(const FFriendData& InFriend) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void SetFriendIsConnected(const FString& UserID, const bool bIsConnected) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void AddFriend(const FFriendData& InFriend) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void RemoveFriend(const FString& UserID) override;

	// Public API
	UFUNCTION(BlueprintCallable, Category = "Friends")
	void LoadFriends(const UDataTable* FriendsDataTable);

private:
	void UpdateFriend(const int Index, const TFunction<void(FFriendData&)>& UpdateFunction);
};
