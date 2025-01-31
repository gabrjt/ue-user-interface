#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendsNotificationsWidgetEntryViewModel.generated.h"

class UFriendsNotificationsWidgetEntryViewModelDataAsset;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendsNotificationsWidgetEntryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float RenderOpacity;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FSlateColor NicknameTextColor;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString NotificationText;

public:
	UFriendsNotificationsWidgetEntryViewModel();

	void SetRenderOpacity(const float InRenderOpacity);

	float GetRenderOpacity() const;

	void SetNicknameTextColor(const FSlateColor& InNicknameTextColor);

	const FSlateColor& GetNicknameTextColor() const;

	void SetNotificationText(const FString& InNotificationText);

	const FString& GetNotificationText() const;

	UFUNCTION(BlueprintCallable)
	void ResetRenderOpacity();

	UFUNCTION(BlueprintCallable)
	void Set(const UFriendsNotificationsWidgetEntryViewModelDataAsset* DataAsset);
};
