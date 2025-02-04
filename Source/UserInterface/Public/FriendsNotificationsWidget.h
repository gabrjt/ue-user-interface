﻿#pragma once

#include "CoreMinimal.h"
#include "FriendListViewWidget.h"
#include "FriendsNotificationsWidget.generated.h"

struct FFriendData;
class UFriendsNotificationsWidgetEntryViewModelDataAsset;

UCLASS()
class USERINTERFACE_API UFriendsNotificationsWidget : public UFriendListViewWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,
		EditInstanceOnly,
		Category = "Settings",
		meta = (Bitmask, BitmaskEnum = "/Script/UserInterface.EFriendsViewModelType", AllowPrivateAccess))
	int32 ViewModelType;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FName ConnectedFriendsViewModelName;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FName DisconnectedFriendsViewModelName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	TSoftObjectPtr<UFriendsNotificationsWidgetEntryViewModelDataAsset> ConnectedNotificationDataAsset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	TSoftObjectPtr<UFriendsNotificationsWidgetEntryViewModelDataAsset> DisconnectedNotificationDataAsset;

	FDelegateHandle OnEntryWidgetGeneratedHandle;

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

	virtual void NativeDestruct() override;

private:
	void OnFriendAdded(const FFriendData& FriendData) const;

	void OnEntryWidgetGenerated(UUserWidget& UserWidget) const;
};
