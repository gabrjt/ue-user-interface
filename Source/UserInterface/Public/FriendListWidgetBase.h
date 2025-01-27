#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidgetBase.generated.h"

class UListView;
class UFriendListViewModelBase;

UCLASS()
class USERINTERFACE_API UFriendListWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UListView* FriendListView;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetViewModel(UFriendListViewModelBase* InFriendListViewModel);
};
