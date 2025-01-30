#pragma once

#include "CoreMinimal.h"
#include "FriendListViewWidget.h"
#include "FriendsWidget.generated.h"

class UTextBlock;
class UButton;
class UVerticalBox;
class UWidgetAnimation;
class UFriendsWidgetViewModelDataAsset;

UCLASS()
class USERINTERFACE_API UFriendsWidget : public UFriendListViewWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* FriendListText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* FriendListCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UVerticalBox* FriendListContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UButton* CollapseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* CollapseButtonText;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim, AllowPrivateAccess))
	TObjectPtr<UWidgetAnimation> CollapseAnimation;

	UPROPERTY(Transient, BlueprintReadWrite, meta=(BindWidgetAnim, AllowPrivateAccess))
	TObjectPtr<UWidgetAnimation> NudgeAnimation;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ViewModelDataLoaded(const UFriendsWidgetViewModelDataAsset* DataAsset);
};
