#include "FriendListWidgetViewModel.h"
#include "FriendListViewModelDataAsset.h"
#include "Components/SlateWrapperTypes.h"

UFriendListWidgetViewModel::UFriendListWidgetViewModel() :
	FriendsCount(0), Title("Friends List"), TextColor(FLinearColor::White), Visibility(ESlateVisibility::Collapsed),
	TargetVisibility(ESlateVisibility::Collapsed), VisibilityText(GetVisibilityTextFromEnum(Visibility)), bIsChangingVisibility(false) {}

void UFriendListWidgetViewModel::SetFriendsCount(const int32& InFriendsCount)
{
	UE_MVVM_SET_PROPERTY_VALUE(FriendsCount, InFriendsCount);
	BroadcastCanChangeVisibility();
}

int32 UFriendListWidgetViewModel::GetFriendsCount() const
{
	return FriendsCount;
}

void UFriendListWidgetViewModel::SetTitle(const FString& InTitle)
{
	UE_MVVM_SET_PROPERTY_VALUE(Title, InTitle);
}

const FString& UFriendListWidgetViewModel::GetTitle() const
{
	return Title;
}

void UFriendListWidgetViewModel::SetTextColor(const FSlateColor& InTextColor)
{
	UE_MVVM_SET_PROPERTY_VALUE(TextColor, InTextColor);
}

const FSlateColor& UFriendListWidgetViewModel::GetTextColor() const
{
	return TextColor;
}

void UFriendListWidgetViewModel::SetVisibilityAndText(const ESlateVisibility& InVisibility)
{
	SetVisibility(InVisibility);
	SetVisibilityTextFromEnum(InVisibility);
}

void UFriendListWidgetViewModel::SetVisibility(const ESlateVisibility& InVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(Visibility, InVisibility);
}

const ESlateVisibility& UFriendListWidgetViewModel::GetVisibility() const
{
	static constexpr ESlateVisibility Visible { ESlateVisibility::Visible };

	if (GetIsChangingVisibility())
	{
		return Visible;
	}

	return Visibility;
}

void UFriendListWidgetViewModel::SetTargetVisibility(const ESlateVisibility& InTargetVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(TargetVisibility, InTargetVisibility);
}

const ESlateVisibility& UFriendListWidgetViewModel::GetTargetVisibility() const
{
	return TargetVisibility;
}

void UFriendListWidgetViewModel::SetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
{
	SetVisibilityText(GetVisibilityTextFromEnum(InVisibility));
}

void UFriendListWidgetViewModel::SetVisibilityText(const FString& InVisibilityText)
{
	UE_MVVM_SET_PROPERTY_VALUE(VisibilityText, InVisibilityText);
}

const FString& UFriendListWidgetViewModel::GetVisibilityText() const
{
	return VisibilityText;
}

void UFriendListWidgetViewModel::SetIsChangingVisibility(const bool& bInIsChangingVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsChangingVisibility, bInIsChangingVisibility);
	BroadcastCanChangeVisibility();
}

bool UFriendListWidgetViewModel::GetIsChangingVisibility() const
{
	return bIsChangingVisibility;
}

ESlateVisibility UFriendListWidgetViewModel::ToggleTargetVisibility()
{
	SetTargetVisibility(GetNextVisibility(TargetVisibility));
	SetVisibilityTextFromEnum(TargetVisibility);
	SetVisibility(ESlateVisibility::Visible);
	SetIsChangingVisibility(true);

	return TargetVisibility;
}

void UFriendListWidgetViewModel::ApplyTargetVisibility()
{
	SetVisibilityAndText(TargetVisibility);
	SetIsChangingVisibility(false);
}

bool UFriendListWidgetViewModel::CanChangeVisibility() const
{
	return FriendsCount != 0 && !GetIsChangingVisibility();
}

void UFriendListWidgetViewModel::Set(const UFriendListViewModelDataAsset* DataAsset)
{
	if (ensure(DataAsset))
	{
		SetTitle(DataAsset->Title);
		SetTextColor(DataAsset->TextColor);
		SetVisibilityAndText(DataAsset->Visibility);
		SetTargetVisibility(DataAsset->Visibility);
	}
}

const FString& UFriendListWidgetViewModel::GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
{
	static const FString Collapsed { "+" };
	static const FString Visible { "-" };

	switch (InVisibility)
	{
		case ESlateVisibility::Collapsed:
			return Collapsed;
		default:
			return Visible;
	}
}

ESlateVisibility UFriendListWidgetViewModel::GetNextVisibility(const ESlateVisibility& InVisibility)
{
	switch (InVisibility)
	{
		case ESlateVisibility::Collapsed:
			return ESlateVisibility::Visible;
		default:
			return ESlateVisibility::Collapsed;
	}
}
