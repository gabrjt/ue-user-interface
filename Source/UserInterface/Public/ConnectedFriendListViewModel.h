#pragma once

#include "CoreMinimal.h"
#include "FriendListViewModelBase.h"
#include "ConnectedFriendListViewModel.generated.h"

UCLASS(BlueprintType)
class USERINTERFACE_API UConnectedFriendListViewModel : public UFriendListViewModelBase
{
	GENERATED_BODY()

public:
	UConnectedFriendListViewModel();

	void OnFriendConnected(const FFriendData& FriendData);

protected:
	virtual void FriendAdded(const int Index) override;
};
