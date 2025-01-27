#pragma once

#include "CoreMinimal.h"
#include "FriendListViewModelBase.h"
#include "ConnectedFriendListViewModel.generated.h"

class UFriendViewModel;

UCLASS(BlueprintType)
class USERINTERFACE_API UConnectedFriendListViewModel : public UFriendListViewModelBase
{
	GENERATED_BODY()

public:
	UConnectedFriendListViewModel();

	/*using UFriendListViewModelBase::AddFriend;
	
	virtual UFriendViewModel* AddFriend(UFriendViewModel* InFriend) override;*/

//protected:
	//virtual void BroadcastFriends() override;
};
