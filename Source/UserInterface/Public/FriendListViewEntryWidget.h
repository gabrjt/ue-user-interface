#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FriendListViewEntryWidget.generated.h"

class UTextBlock;

UCLASS()
class USERINTERFACE_API UFriendListViewEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	// Your entry widget properties
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* NicknameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* IsConnectedText;
};
