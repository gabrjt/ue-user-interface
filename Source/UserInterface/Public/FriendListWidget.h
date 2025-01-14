// FriendListWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidget.generated.h"

class UListView;
class UFriendListViewModel;

UCLASS()
class USERINTERFACE_API UFriendListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* FriendListView;

	UPROPERTY()
	UFriendListViewModel* ViewModel;

	void BindViewModel();
};