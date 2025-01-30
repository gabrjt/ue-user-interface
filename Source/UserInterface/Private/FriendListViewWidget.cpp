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
	return Cast<UFriendsViewModel>(
		GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection()->FindViewModelInstance({
			UFriendsViewModel::StaticClass(),
			InViewModelName
		}));
}

void UFriendListViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UFriendsViewModel* ViewModel { NewObject<UFriendsViewModel>(this) };

	GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection()->AddViewModelInstance({
			UFriendsViewModel::StaticClass(),
			ViewModelName
		},
		ViewModel);

	SetViewModel(ViewModel);
}
