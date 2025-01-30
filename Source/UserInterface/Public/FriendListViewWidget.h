#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListViewWidget.generated.h"

class UListView;
class UFriendsViewModel;

UCLASS(Abstract)
class USERINTERFACE_API UFriendListViewWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UListView* FriendListView;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetViewModel(UFriendsViewModel* InFriendsViewModel);
};
