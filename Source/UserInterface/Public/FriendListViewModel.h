#pragma once

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

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FSlateColor TextColor;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	ESlateVisibility Visibility;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	FString VisibilityText;

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

	void SetTextColor(const FSlateColor& InTextColor);

	const FSlateColor& GetTextColor() const;

	UFUNCTION(BlueprintCallable)
	void SetVisibilityAndText(const ESlateVisibility& InVisibility);

	void SetVisibility(const ESlateVisibility& InVisibility);

	const ESlateVisibility& GetVisibility() const;

	UFUNCTION(BlueprintCallable)
	void SetVisibilityTextFromEnum(const ESlateVisibility& InVisibility);

	void SetVisibilityText(const FString& InVisibilityText);

	const FString& GetVisibilityText() const;

	UFUNCTION(BlueprintCallable)
	void ToggleVisibility();

	UFUNCTION(BlueprintPure, FieldNotify)
	int GetFriendsCount() const;

private:
	static const FString& GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility);

	FORCEINLINE void AddFriend(const FFriendData& InFriend)
	{
		Friends.Add(UFriendViewModel::Create(this, InFriend));
	}

	FORCEINLINE void BroadcastFriends()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Friends);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetFriendsCount);
	}
};
