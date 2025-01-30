﻿#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendListWidgetViewModel.generated.h"

class UFriendListViewModelDataAsset;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendListWidgetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	int32 FriendsCount;

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

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter="SetIsChangingVisibility", Getter="GetIsChangingVisibility", meta=(AllowPrivateAccess))
	bool bIsChangingVisibility;

public:
	UFriendListWidgetViewModel();

	void SetFriendsCount(const int32& InFriendsCount);

	int32 GetFriendsCount() const;

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

	void SetIsChangingVisibility(const bool& bInIsChangingVisibility);

	bool GetIsChangingVisibility() const;

	UFUNCTION(BlueprintCallable)
	ESlateVisibility ToggleTargetVisibility();

	UFUNCTION(BlueprintCallable)
	void ApplyTargetVisibility();

	UFUNCTION(BlueprintPure, FieldNotify)
	bool CanChangeVisibility() const;

	void Set(const UFriendListViewModelDataAsset* DataAsset);

private:
	static const FString& GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility);

	static ESlateVisibility GetNextVisibility(const ESlateVisibility& InVisibility);

	FORCEINLINE void BroadcastCanChangeVisibility()
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanChangeVisibility);
	}
};
