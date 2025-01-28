#pragma once

#include "CoreMinimal.h"
#include "FriendViewModel.h"
#include "MVVMViewModelBase.h"
#include "FriendListViewModelBase.generated.h"

struct FFriendData;

DECLARE_DELEGATE_OneParam(FOnFriendAdded, const FFriendData&);

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	FOnFriendAdded OnFriendAdded;

	UFriendListViewModelBase();

	virtual ~UFriendListViewModelBase() override;

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
		const int Index { Friends.Add(UFriendViewModel::Create(this, InFriend)) };

		FriendAdded(Index);

		return Index;
	}

protected:
	virtual void FriendAdded(const int Index);

	virtual void BroadcastFriends();

	FORCEINLINE void BroadcastGetLastAddedFriend()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetLastAddedFriend);
	}
};
