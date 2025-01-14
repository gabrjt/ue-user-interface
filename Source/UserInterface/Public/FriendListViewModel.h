// FriendListViewModel.h
#pragma once

#include "CoreMinimal.h"
#include "FriendViewModel.h"
#include "MVVMViewModelBase.h"
#include "FriendListViewModel.generated.h"

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	TArray<UFriendViewModel*> Friends;

public:
	UFriendListViewModel();

	// Getter for the Friends array
	const TArray<UFriendViewModel*>& GetFriends() const;

	// Add a friend to the list
	UFUNCTION(BlueprintCallable)
	void AddFriend(UFriendViewModel* Friend);

	// Remove a friend from the list
	UFUNCTION(BlueprintCallable)
	void RemoveFriend(const FString& UserID);

	// Clear all friends
	UFUNCTION(BlueprintCallable)
	void ClearFriends();

	// Update or add a friend
	UFUNCTION(BlueprintCallable)
	void UpdateFriend(const FFriendData& FriendData);
};
