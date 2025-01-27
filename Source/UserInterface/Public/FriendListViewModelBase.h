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
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	UFriendListViewModelBase();

	void SetFriends(const TArray<UFriendViewModel*>& InFriends);
	
	const TArray<UFriendViewModel*>& GetFriends() const;

	UFUNCTION(BlueprintCallable)
	void RemoveFriend(const FString& UserID);

	UFUNCTION(BlueprintCallable)
	void ClearFriends();

	UFUNCTION(BlueprintCallable)
	UFriendViewModel* UpdateFriend(const FFriendData& InFriend);

	UFUNCTION(BlueprintPure, FieldNotify)
	int GetFriendsCount() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	UFriendViewModel* FriendAdded() const;
	
	FORCEINLINE UFriendViewModel* AddFriend(const FFriendData& InFriend)
	{
		return AddFriend(UFriendViewModel::Create(this, InFriend));
	}

	virtual UFriendViewModel* AddFriend(UFriendViewModel* InFriend);

protected:
	virtual void BroadcastFriends();

	FORCEINLINE void BroadcastFriendAdded()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(FriendAdded);
	}
};
