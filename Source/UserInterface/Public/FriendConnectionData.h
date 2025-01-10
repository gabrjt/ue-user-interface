// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FriendConnectionData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct USERINTERFACE_API FFriendConnectionData : public FTableRowBase
{
	GENERATED_BODY()

	// Unique identifier for the friend
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString UserID;

	// Display name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString Nickname;

	// Player level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	int32 Level;

	// Online status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	bool bIsConnected;

	// Last seen timestamp (stored as string for simplicity in this example)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString LastSeen;

	// Optional: Current activity/status message
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString StatusMessage;

	FFriendConnectionData();
};
