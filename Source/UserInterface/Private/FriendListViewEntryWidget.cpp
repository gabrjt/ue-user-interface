#include "FriendListViewEntryWidget.h"
#include "FriendViewModel.h"
#include "Components/TextBlock.h"

void UFriendListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// Cast to your data type and update the widget
	if (UFriendViewModel* Data = Cast<UFriendViewModel>(ListItemObject))
	{
		NicknameText->SetText(FText::FromString(Data->GetNickname()));
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
