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
	virtual FDelegateHandle SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback) = 0;

	virtual void UnsubscribeOnFriendUpdated(FDelegateHandle Handle) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	void LoadFriends();

	virtual void LoadFriends_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	bool GetFriend(const FString& UserID, FFriendData& OutFriend) const;

	virtual bool GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetFriends() const;

	virtual TArray<FFriendData> GetFriends_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetConnectedFriends() const;

	virtual TArray<FFriendData> GetConnectedFriends_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	TArray<FFriendData> GetDisconnectedFriends() const;

	virtual TArray<FFriendData> GetDisconnectedFriends_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	void UpdateFriend(const FFriendData& InFriend);

	virtual void UpdateFriend_Implementation(const FFriendData& InFriend);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	void SetFriendIsConnected(const FString& UserID, const bool bIsConnected);

	virtual void SetFriendIsConnected_Implementation(const FString& UserID, const bool bIsConnected);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	void AddFriend(const FFriendData& InFriend);

	virtual void AddFriend_Implementation(const FFriendData& InFriend);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Friends")
	void RemoveFriend(const FString& UserID);

	virtual void RemoveFriend_Implementation(const FString& UserID);
};
