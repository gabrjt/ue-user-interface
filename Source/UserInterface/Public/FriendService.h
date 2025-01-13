// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendData.h"
#include "UObject/Interface.h"
#include "FriendService.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendUpdated, const FFriendData&);
using FOnFriendUpdatedDelegate = FOnFriendUpdated::FDelegate;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendUpdatedDelegateDynamic, FFriendData, FriendData);

UINTERFACE(MinimalAPI, Blueprintable)
class UFriendService : public UInterface
{
	GENERATED_BODY()
};

class USERINTERFACE_API IFriendService
{
	GENERATED_BODY()

public:
	virtual bool GetFriend(const FString& UserID, FFriendData& OutFriend) const = 0;

	virtual const TArray<FFriendData>& GetFriends() const = 0;

	virtual TArray<FFriendData> GetConnectedFriends() const = 0;

	virtual TArray<FFriendData> GetDisconnectedFriends() const = 0;

	virtual FDelegateHandle SubscribeOnFriendUpdated(const FOnFriendUpdatedDelegate& Callback) = 0;

	virtual void UnsubscribeOnFriendUpdated(FDelegateHandle Handle) = 0;
};
