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
	UFriendViewModel* GetLastAddedFriend() const;

	FORCEINLINE int AddFriend(const FFriendData& InFriend)
	{
		const int Index{Friends.Add(UFriendViewModel::Create(this, InFriend))};

		OnFriendAdded(Index);

		return Index;
	}

protected:
	virtual void OnFriendAdded(int Index);

	virtual void BroadcastFriends();

	FORCEINLINE void BroadcastGetLastAddedFriend()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetLastAddedFriend);
	}
};
