#include "FriendListViewEntryWidget.h"
#include "FriendViewModel.h"
#include "Components/TextBlock.h"

void UFriendListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// Cast to your data type and update the widget
	ViewModel = Cast<UFriendViewModel>(ListItemObject);

	if (ViewModel)
	{
		NicknameText->SetText(FText::FromString(ViewModel->GetNickname()));
		IsConnectedText->SetText(FText::FromString(LexToString(ViewModel->GetIsConnected())));
	}
}

void UFriendListViewEntryWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UFriendListViewEntryWidget::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);
}
