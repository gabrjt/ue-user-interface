#include "FriendNotificationWidgetViewModel.h"

UFriendNotificationWidgetViewModel::UFriendNotificationWidgetViewModel():
	RenderOpacity(0)
{
}

void UFriendNotificationWidgetViewModel::SetRenderOpacity(const float InRenderOpacity)
{
	RenderOpacity = InRenderOpacity;
}

float UFriendNotificationWidgetViewModel::GetRenderOpacity() const
{
	return RenderOpacity;
}

void UFriendNotificationWidgetViewModel::ResetRenderOpacity()
{
	SetRenderOpacity(0);
}
