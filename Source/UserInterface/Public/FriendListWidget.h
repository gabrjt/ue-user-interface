#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidget.generated.h"

class UListView;
class UTextBlock;
class UButton;
class UVerticalBox;
class UFriendListViewModel;

UCLASS()
class USERINTERFACE_API UFriendListWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UListView* FriendListView;

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

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetViewModel(UFriendListViewModel* InFriendListViewModel);

	UFUNCTION(BlueprintImplementableEvent)
	void ViewModelDataLoaded(UFriendListViewModel* InFriendListViewModel);
};
