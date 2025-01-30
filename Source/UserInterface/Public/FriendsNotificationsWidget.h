#pragma once

#include "CoreMinimal.h"
#include "FriendListViewWidget.h"
#include "FriendsNotificationsWidget.generated.h"

UCLASS()
class USERINTERFACE_API UFriendsNotificationsWidget : public UFriendListViewWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FName ConnectedFriendsViewModelName;

protected:
	virtual void NativePreConstruct() override;
};
