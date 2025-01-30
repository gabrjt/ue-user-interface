#include "FriendListViewWidget.h"
#include "FriendsViewModel.h"
#include "MVVMGameSubsystem.h"

void UFriendListViewWidget::SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel) {}

void UFriendListViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UFriendsViewModel* ViewModel { NewObject<UFriendsViewModel>() };

	GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection()->AddViewModelInstance({
			TSubclassOf<UFriendsViewModel>(),
			ViewModelName
		},
		ViewModel);

	SetViewModel(ViewModel);
}
