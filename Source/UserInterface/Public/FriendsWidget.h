#pragma once

#include "CoreMinimal.h"
#include "FriendListViewWidget.h"
#include "FriendsWidget.generated.h"

enum class EFriendsViewModelType : uint8;
class UTextBlock;
class UButton;
class UVerticalBox;
class UWidgetAnimation;
class UFriendsWidgetViewModel;
class UFriendsWidgetViewModelDataAsset;

UCLASS()
class USERINTERFACE_API UFriendsWidget : public UFriendListViewWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	EFriendsViewModelType ViewModelType;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FName WidgetViewModelName;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	TSoftObjectPtr<UFriendsWidgetViewModelDataAsset> FriendsWidgetViewModelDataAsset;

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
	void SetWidgetViewModel(UFriendsWidgetViewModel* InFriendsWidgetViewModel);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetViewModelDataLoaded(const UFriendsWidgetViewModelDataAsset* DataAsset);

protected:
	virtual void NativeOnInitialized() override;

	virtual void SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel) override;

private:
	void OnDataAssetsLoaded();
};
