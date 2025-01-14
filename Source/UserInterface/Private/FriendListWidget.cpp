// FriendListWidget.cpp
#include "FriendListWidget.h"
#include "FriendListViewModel.h"
#include "Components/ListView.h"

void UFriendListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Create the ViewModel
	ViewModel = NewObject<UFriendListViewModel>(this);

	BindViewModel();
}

void UFriendListWidget::BindViewModel()
{
	if (!ViewModel || !FriendListView)
	{
		return;
	}

	// Clear existing items
	FriendListView->ClearListItems();

	// Add initial items
	for (UFriendViewModel* Friend : ViewModel->GetFriends())
	{
		FriendListView->AddItem(Friend);
	}

	// Bind to changes in the Friends array
	/*ViewModel->BindFieldNotify(GET_MEMBER_NAME_CHECKED(UFriendListViewModel, Friends),
		[this](const TArray<UFriendViewModel*>& NewFriends)
		{
			if (FriendListView)
			{
				FriendListView->ClearListItems();
				for (UFriendViewModel* Friend : NewFriends)
				{
					FriendListView->AddItem(Friend);
				}
			}
		});*/
}