#include "FriendsWidgetViewModel.h"
#include "FriendsViewModel.h"
#include "FriendsWidgetViewModelDataAsset.h"
#include "Components/SlateWrapperTypes.h"

UFriendsWidgetViewModel::UFriendsWidgetViewModel() :
	FriendsCount(0), Title("Friends List"), TextColor(FLinearColor::White), Visibility(ESlateVisibility::Collapsed),
	TargetVisibility(ESlateVisibility::Collapsed), VisibilityText(GetVisibilityTextFromEnum(Visibility)), bIsChangingVisibility(false) {}

void UFriendsWidgetViewModel::SetFriendsCount(const int32& InFriendsCount)
{
	UE_MVVM_SET_PROPERTY_VALUE(FriendsCount, InFriendsCount);
	BroadcastCanChangeVisibility();
}

int32 UFriendsWidgetViewModel::GetFriendsCount() const
{
	return FriendsCount;
}

void UFriendsWidgetViewModel::SetTitle(const FString& InTitle)
{
	UE_MVVM_SET_PROPERTY_VALUE(Title, InTitle);
}

const FString& UFriendsWidgetViewModel::GetTitle() const
{
	return Title;
}

void UFriendsWidgetViewModel::SetTextColor(const FSlateColor& InTextColor)
{
	UE_MVVM_SET_PROPERTY_VALUE(TextColor, InTextColor);
}

const FSlateColor& UFriendsWidgetViewModel::GetTextColor() const
{
	return TextColor;
}

void UFriendsWidgetViewModel::SetVisibilityAndText(const ESlateVisibility& InVisibility)
{
	SetVisibility(InVisibility);
	SetVisibilityTextFromEnum(InVisibility);
}

void UFriendsWidgetViewModel::SetVisibility(const ESlateVisibility& InVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(Visibility, InVisibility);
}

const ESlateVisibility& UFriendsWidgetViewModel::GetVisibility() const
{
	static constexpr ESlateVisibility Visible { ESlateVisibility::Visible };

	if (GetIsChangingVisibility())
	{
		return Visible;
	}

	return Visibility;
}

void UFriendsWidgetViewModel::SetTargetVisibility(const ESlateVisibility& InTargetVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(TargetVisibility, InTargetVisibility);
}

const ESlateVisibility& UFriendsWidgetViewModel::GetTargetVisibility() const
{
	return TargetVisibility;
}

void UFriendsWidgetViewModel::SetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
{
	SetVisibilityText(GetVisibilityTextFromEnum(InVisibility));
}

void UFriendsWidgetViewModel::SetVisibilityText(const FString& InVisibilityText)
{
	UE_MVVM_SET_PROPERTY_VALUE(VisibilityText, InVisibilityText);
}

const FString& UFriendsWidgetViewModel::GetVisibilityText() const
{
	return VisibilityText;
}

void UFriendsWidgetViewModel::SetIsChangingVisibility(const bool& bInIsChangingVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsChangingVisibility, bInIsChangingVisibility);
	BroadcastCanChangeVisibility();
}

bool UFriendsWidgetViewModel::GetIsChangingVisibility() const
{
	return bIsChangingVisibility;
}

ESlateVisibility UFriendsWidgetViewModel::ToggleTargetVisibility()
{
	SetTargetVisibility(GetNextVisibility(TargetVisibility));
	SetVisibilityTextFromEnum(TargetVisibility);
	SetVisibility(ESlateVisibility::Visible);
	SetIsChangingVisibility(true);

	return TargetVisibility;
}

void UFriendsWidgetViewModel::ApplyTargetVisibility()
{
	SetVisibilityAndText(TargetVisibility);
	SetIsChangingVisibility(false);
}

bool UFriendsWidgetViewModel::CanChangeVisibility() const
{
	return FriendsCount != 0 && !GetIsChangingVisibility();
}

void UFriendsWidgetViewModel::Set(const UFriendsWidgetViewModelDataAsset* DataAsset)
{
	if (ensure(DataAsset))
	{
		SetTitle(DataAsset->Title);
		SetTextColor(DataAsset->TextColor);
		SetVisibilityAndText(DataAsset->Visibility);
		SetTargetVisibility(DataAsset->Visibility);
	}
}

const FString& UFriendsWidgetViewModel::GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
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

ESlateVisibility UFriendsWidgetViewModel::GetNextVisibility(const ESlateVisibility& InVisibility)
{
	switch (InVisibility)
	{
		case ESlateVisibility::Collapsed:
			return ESlateVisibility::Visible;
		default:
			return ESlateVisibility::Collapsed;
	}
}
