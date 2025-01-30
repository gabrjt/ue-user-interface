#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FriendsWidgetEntry.generated.h"

class UTextBlock;
class UWidgetAnimation;

UCLASS()
class USERINTERFACE_API UFriendsWidgetEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* NicknameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* LevelText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* StatusMessageText;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim, AllowPrivateAccess))
	TObjectPtr<UWidgetAnimation> LevelUpAnimation;
};
