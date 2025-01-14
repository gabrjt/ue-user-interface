#pragma once

#include "FriendViewModel.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FriendListViewEntryWidget.generated.h"

class UTextBlock;

UCLASS()
class USERINTERFACE_API UFriendListViewEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	// Optional: Handle selection changes
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	// Optional: Handle entry expansion
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;

protected:
	// Your entry widget properties
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NicknameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* IsConnectedText;

	UPROPERTY()
	UFriendViewModel* ViewModel;
};
