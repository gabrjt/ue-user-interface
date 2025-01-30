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
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FName ViewModelName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UListView* FriendListView;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetViewModel(UFriendsViewModel* InFriendsViewModel);

	virtual void SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel);

	UFriendsViewModel* GetViewModel() const;

	UFriendsViewModel* GetViewModel(const FName& InViewModelName) const;

protected:
	virtual void NativeOnInitialized() override;
};
