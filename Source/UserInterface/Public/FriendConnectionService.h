// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendConnectionData.h"
#include "UObject/Interface.h"
#include "FriendConnectionService.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendStatusChanged, const FFriendConnectionData&);
using FOnFriendStatusChangedDelegate = FOnFriendStatusChanged::FDelegate;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendStatusChangedDynamic, FFriendConnectionData, FriendData);

UINTERFACE(MinimalAPI, Blueprintable)
class UFriendConnectionService : public UInterface
{
	GENERATED_BODY()
};

class USERINTERFACE_API IFriendConnectionService
{
	GENERATED_BODY()

public:
	virtual TArray<FFriendConnectionData> GetConnectedFriends() const = 0;

	virtual TArray<FFriendConnectionData> GetDisconnectedFriends() const = 0;

	virtual FDelegateHandle RegisterForFriendStatusUpdates(const FOnFriendStatusChangedDelegate& Callback) = 0;

	virtual void UnregisterFromFriendStatusUpdates(FDelegateHandle Handle) = 0;
};
