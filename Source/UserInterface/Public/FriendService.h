// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendData.h"
#include "UObject/Interface.h"
#include "FriendService.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendUpdated, const FFriendData&);
using FOnFriendUpdatedDelegate = FOnFriendUpdated::FDelegate;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendUpdatedDelegateDynamic, FFriendData, FriendData);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UFriendService : public UInterface
{
	GENERATED_BODY()
};

class USERINTERFACE_API IFriendService
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	bool GetFriend(const FString& UserID, FFriendData& OutFriend) const;

	virtual bool GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetFriends() const;

	virtual TArray<FFriendData> GetFriends_Implementation() const { return TArray<FFriendData>(); }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetConnectedFriends() const;

	virtual TArray<FFriendData> GetConnectedFriends_Implementation() const { return TArray<FFriendData>(); }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetDisconnectedFriends() const;

	virtual TArray<FFriendData> GetDisconnectedFriends_Implementation() const { return TArray<FFriendData>(); }

	virtual FDelegateHandle SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback) = 0;

	virtual void UnsubscribeOnFriendUpdated(FDelegateHandle Handle) = 0;

	virtual void UpdateFriend(const FFriendData& InFriend) = 0;

	virtual void SetFriendIsConnected(const FString& UserID, const bool bIsConnected) = 0;

	virtual void AddFriend(const FFriendData& InFriend) = 0;

	virtual void RemoveFriend(const FString& UserID) = 0;
};
