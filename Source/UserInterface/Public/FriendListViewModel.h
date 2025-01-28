#pragma once

#include "CoreMinimal.h"
#include "FriendListViewModelBase.h"
#include "FriendListViewModel.generated.h"

struct FFriendData;
class UFriendListViewModelDataAsset;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListViewModel : public UFriendListViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString Title;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FSlateColor TextColor;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	ESlateVisibility Visibility;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	ESlateVisibility TargetVisibility;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, meta=(AllowPrivateAccess))
	FString VisibilityText;

public:
	UFriendListViewModel();

	void SetFriendsFromData(const TArray<FFriendData>& InFriends);

	void SetTitle(const FString& InTitle);

	const FString& GetTitle() const;

	void SetTextColor(const FSlateColor& InTextColor);

	const FSlateColor& GetTextColor() const;

	UFUNCTION(BlueprintCallable)
	void SetVisibilityAndText(const ESlateVisibility& InVisibility);

	void SetVisibility(const ESlateVisibility& InVisibility);

	const ESlateVisibility& GetVisibility() const;

	void SetTargetVisibility(const ESlateVisibility& InTargetVisibility);

	const ESlateVisibility& GetTargetVisibility() const;

	UFUNCTION(BlueprintCallable)
	void SetVisibilityTextFromEnum(const ESlateVisibility& InVisibility);

	void SetVisibilityText(const FString& InVisibilityText);

	const FString& GetVisibilityText() const;

	UFUNCTION(BlueprintCallable)
	void ToggleVisibility();

	UFUNCTION(BlueprintCallable)
	ESlateVisibility ToggleTargetVisibility();

	UFUNCTION(BlueprintCallable)
	void ApplyTargetVisibility();

	UFUNCTION(BlueprintPure, FieldNotify)
	bool IsChangingVisibility() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	bool CanChangeVisibility() const;

	void Set(const UFriendListViewModelDataAsset* DataAsset);

protected:
	virtual void BroadcastFriends() override;

private:
	static const FString& GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility);

	static ESlateVisibility GetNextVisibility(const ESlateVisibility& InVisibility);
};
