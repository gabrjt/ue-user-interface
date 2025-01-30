#include "FriendListViewWidget.h"
#include "FriendsViewModel.h"
#include "MVVMGameSubsystem.h"

void UFriendListViewWidget::SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel) {}

UFriendsViewModel* UFriendListViewWidget::GetViewModel() const
{
	return GetViewModel(ViewModelName);
}

UFriendsViewModel* UFriendListViewWidget::GetViewModel(const FName& InViewModelName) const
{
	if (const UMVVMViewModelCollectionObject* ViewModelCollection { GetViewModelCollection() })
	{
		return Cast<UFriendsViewModel>(ViewModelCollection->FindViewModelInstance({
			UFriendsViewModel::StaticClass(),
			InViewModelName
		}));
	}

	return nullptr;
}

void UFriendListViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UFriendsViewModel* ViewModel { NewObject<UFriendsViewModel>(this) }; GetViewModelCollection()->
		AddViewModelInstance({ UFriendsViewModel::StaticClass(), ViewModelName }, ViewModel))
	{
		SetViewModel(ViewModel);
	}
}

void UFriendListViewWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (UMVVMViewModelCollectionObject* ViewModelCollection { GetViewModelCollection() })
	{
		ViewModelCollection->RemoveViewModel({ UFriendsViewModel::StaticClass(), ViewModelName });
	}
}

UMVVMViewModelCollectionObject* UFriendListViewWidget::GetViewModelCollection() const
{
	if (const UGameInstance* GameInstance { GetGameInstance() })
	{
		return GameInstance->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();
	}

	return nullptr;
}
