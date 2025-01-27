#pragma once

#include "CoreMinimal.h"
#include "FriendViewModel.h"
#include "MVVMViewModelBase.h"
#include "FriendListViewModelBase.generated.h"

struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	UFriendListViewModelBase();

	const TArray<UFriendViewModel*>& GetFriends() const;

	UFUNCTION(BlueprintCallable)
	void RemoveFriend(const FString& UserID);

	UFUNCTION(BlueprintCallable)
	void ClearFriends();

	UFUNCTION(BlueprintCallable)
	void UpdateFriend(const FFriendData& InFriend);

	UFUNCTION(BlueprintPure, FieldNotify)
	int GetFriendsCount() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	UFriendViewModel* FriendAdded() const;

protected:
	FORCEINLINE void AddFriend(const FFriendData& InFriend)
	{
		Friends.Add(UFriendViewModel::Create(this, InFriend));

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(FriendAdded);
	}

	virtual void BroadcastFriends();
};
