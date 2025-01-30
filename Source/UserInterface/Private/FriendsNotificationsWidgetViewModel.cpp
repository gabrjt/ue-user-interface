#include "FriendsNotificationsWidgetViewModel.h"

UFriendsNotificationsWidgetViewModel::UFriendsNotificationsWidgetViewModel():
	RenderOpacity(0)
{
}

void UFriendsNotificationsWidgetViewModel::SetRenderOpacity(const float InRenderOpacity)
{
	RenderOpacity = InRenderOpacity;
}

float UFriendsNotificationsWidgetViewModel::GetRenderOpacity() const
{
	return RenderOpacity;
}

void UFriendsNotificationsWidgetViewModel::ResetRenderOpacity()
{
	SetRenderOpacity(0);
}
