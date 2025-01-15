﻿#pragma once

#include "CoreMinimal.h"
#include "FriendViewModel.h"
#include "MVVMViewModelBase.h"
#include "FriendListViewModel.generated.h"

struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString Title;

public:
	UFriendListViewModel();

	const TArray<UFriendViewModel*>& GetFriends() const;

	UFUNCTION(BlueprintCallable)
	void SetFriends(const TArray<FFriendData>& InFriends);

	UFUNCTION(BlueprintCallable)
	void RemoveFriend(const FString& UserID);

	UFUNCTION(BlueprintCallable)
	void ClearFriends();

	UFUNCTION(BlueprintCallable)
	void UpdateFriend(const FFriendData& InFriend);

	void SetTitle(const FString& InTitle);

	const FString& GetTitle() const;

private:
	FORCEINLINE void AddFriend(const FFriendData& InFriend)
	{
		Friends.Add(UFriendViewModel::Create(this, InFriend));
	}
};
