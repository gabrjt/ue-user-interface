#include "FriendsNotificationsWidgetEntryViewModel.h"
#include "FriendsNotificationsWidgetEntryViewModelDataAsset.h"

UFriendsNotificationsWidgetEntryViewModel::UFriendsNotificationsWidgetEntryViewModel()
	: RenderOpacity(0) {}

void UFriendsNotificationsWidgetEntryViewModel::SetRenderOpacity(const float InRenderOpacity)
{
	UE_MVVM_SET_PROPERTY_VALUE(RenderOpacity, InRenderOpacity);
}

float UFriendsNotificationsWidgetEntryViewModel::GetRenderOpacity() const
{
	return RenderOpacity;
}

void UFriendsNotificationsWidgetEntryViewModel::SetNicknameTextColor(const FSlateColor& InNicknameTextColor)
{
	UE_MVVM_SET_PROPERTY_VALUE(NicknameTextColor, InNicknameTextColor);
}

const FSlateColor& UFriendsNotificationsWidgetEntryViewModel::GetNicknameTextColor() const
{
	return NicknameTextColor;
}

void UFriendsNotificationsWidgetEntryViewModel::SetNotificationText(const FString& InNotificationText)
{
	UE_MVVM_SET_PROPERTY_VALUE(NotificationText, InNotificationText);
}

const FString& UFriendsNotificationsWidgetEntryViewModel::GetNotificationText() const
{
	return NotificationText;
}

void UFriendsNotificationsWidgetEntryViewModel::ResetRenderOpacity()
{
	SetRenderOpacity(0);
}

void UFriendsNotificationsWidgetEntryViewModel::Set(const UFriendsNotificationsWidgetEntryViewModelDataAsset* DataAsset)
{
	if (ensure(DataAsset))
	{
		SetNicknameTextColor(DataAsset->NicknameTextColor);
		SetNotificationText(DataAsset->NotificationText);
	}
}
