﻿#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FriendsNotificationsWidgetEntry.generated.h"

class UBorder;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class USERINTERFACE_API UFriendsNotificationsWidgetEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UBorder* Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* NicknameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* NotificationText;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim, AllowPrivateAccess))
	TObjectPtr<UWidgetAnimation> ToastAnimation;
};
