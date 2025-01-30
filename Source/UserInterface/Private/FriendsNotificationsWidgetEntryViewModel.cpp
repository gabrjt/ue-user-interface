#include "FriendsNotificationsWidgetEntryViewModel.h"

UFriendsNotificationsWidgetEntryViewModel::UFriendsNotificationsWidgetEntryViewModel()
	: RenderOpacity(0) {}

void UFriendsNotificationsWidgetEntryViewModel::SetRenderOpacity(const float InRenderOpacity)
{
	RenderOpacity = InRenderOpacity;
}

float UFriendsNotificationsWidgetEntryViewModel::GetRenderOpacity() const
{
	return RenderOpacity;
}

void UFriendsNotificationsWidgetEntryViewModel::ResetRenderOpacity()
{
	SetRenderOpacity(0);
}
