#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendListViewModel.generated.h"

class UFriendViewModel;
struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	UFriendListViewModel();

	const TArray<UFriendViewModel*>& GetFriends() const;

	UFUNCTION(BlueprintCallable)
	void SetFriends(const TArray<FFriendData>& InFriends);

	UFUNCTION(BlueprintCallable)
	void AddFriend(UFriendViewModel* Friend);

	UFUNCTION(BlueprintCallable)
	void RemoveFriend(const FString& UserID);

	UFUNCTION(BlueprintCallable)
	void ClearFriends();

	UFUNCTION(BlueprintCallable)
	void UpdateFriend(const FFriendData& InFriend);
};
