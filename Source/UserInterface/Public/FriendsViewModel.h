#pragma once

#include "CoreMinimal.h"
#include "FriendViewModel.h"
#include "MVVMViewModelBase.h"
#include "FriendsViewModel.generated.h"

struct FFriendData;

DECLARE_DELEGATE_OneParam(FOnFriendAdded, const FFriendData&);

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	FOnFriendAdded OnFriendAdded;

	UFriendsViewModel();

	virtual ~UFriendsViewModel() override;

	void SetFriendsFromData(const TArray<FFriendData>& InFriends);

	void SetFriends(const TArray<UFriendViewModel*>& InFriends);

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
	UFriendViewModel* GetLastAddedFriend() const;

	void AddFriend(const FFriendData& InFriend);

private:
	FORCEINLINE void AddFriend_Internal(const FFriendData& InFriend)
	{
		Friends.Add(UFriendViewModel::Create(this, InFriend));
	}

	FORCEINLINE void BroadcastFriends()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
	}

	FORCEINLINE void BroadcastGetLastAddedFriend()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetLastAddedFriend);
	}
};
