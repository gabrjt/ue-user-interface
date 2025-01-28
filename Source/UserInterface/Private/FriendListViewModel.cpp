#include "FriendListViewModel.h"
#include "FriendData.h"
#include "FriendListViewModelDataAsset.h"
#include "Components/SlateWrapperTypes.h"

UFriendListViewModel::UFriendListViewModel()
	: UFriendListViewModelBase()
	, Title("Friends List")
	, TextColor(FLinearColor::White)
	, Visibility(ESlateVisibility::Collapsed)
	, TargetVisibility(ESlateVisibility::Collapsed)
	, VisibilityText(GetVisibilityTextFromEnum(Visibility))
{
}

void UFriendListViewModel::SetFriendsFromData(const TArray<FFriendData>& InFriends)
{
	Friends.Reset(InFriends.Num());

	for (auto& Friend : InFriends)
	{
		AddFriend(Friend);
	}

	BroadcastFriends();
}

void UFriendListViewModel::SetTitle(const FString& InTitle)
{
	UE_MVVM_SET_PROPERTY_VALUE(Title, InTitle);
}

const FString& UFriendListViewModel::GetTitle() const
{
	return Title;
}

void UFriendListViewModel::SetTextColor(const FSlateColor& InTextColor)
{
	UE_MVVM_SET_PROPERTY_VALUE(TextColor, InTextColor);
}

const FSlateColor& UFriendListViewModel::GetTextColor() const
{
	return TextColor;
}

void UFriendListViewModel::SetVisibilityAndText(const ESlateVisibility& InVisibility)
{
	SetVisibility(InVisibility);
	SetVisibilityTextFromEnum(InVisibility);
}

void UFriendListViewModel::SetVisibility(const ESlateVisibility& InVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(Visibility, InVisibility);
}

const ESlateVisibility& UFriendListViewModel::GetVisibility() const
{
	static constexpr ESlateVisibility Visible { ESlateVisibility::Visible };

	if (IsChangingVisibility())
	{
		return Visible;
	}

	return Visibility;
}

void UFriendListViewModel::SetTargetVisibility(const ESlateVisibility& InTargetVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(TargetVisibility, InTargetVisibility);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanChangeVisibility);
}

const ESlateVisibility& UFriendListViewModel::GetTargetVisibility() const
{
	return TargetVisibility;
}

void UFriendListViewModel::SetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
{
	SetVisibilityText(GetVisibilityTextFromEnum(InVisibility));
}

void UFriendListViewModel::SetVisibilityText(const FString& InVisibilityText)
{
	UE_MVVM_SET_PROPERTY_VALUE(VisibilityText, InVisibilityText);
}

const FString& UFriendListViewModel::GetVisibilityText() const
{
	return VisibilityText;
}

void UFriendListViewModel::ToggleVisibility()
{
	SetVisibilityAndText(GetNextVisibility(Visibility));
}

ESlateVisibility UFriendListViewModel::ToggleTargetVisibility()
{
	SetTargetVisibility(GetNextVisibility(TargetVisibility));
	SetVisibilityTextFromEnum(TargetVisibility);
	SetVisibility(ESlateVisibility::Visible);

	return TargetVisibility;
}

void UFriendListViewModel::ApplyTargetVisibility()
{
	SetVisibilityAndText(TargetVisibility);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanChangeVisibility);
}

bool UFriendListViewModel::IsChangingVisibility() const
{
	return Visibility != TargetVisibility;
}

bool UFriendListViewModel::CanChangeVisibility() const
{
	return Friends.Num() != 0 && !IsChangingVisibility();
}

void UFriendListViewModel::Set(const UFriendListViewModelDataAsset* DataAsset)
{
	if (ensure(DataAsset))
	{
		SetTitle(DataAsset->Title);
		SetTextColor(DataAsset->TextColor);
		SetVisibilityAndText(DataAsset->Visibility);
		SetTargetVisibility(DataAsset->Visibility);
	}
}

void UFriendListViewModel::BroadcastFriends()
{
	Super::BroadcastFriends();

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanChangeVisibility);
}

const FString& UFriendListViewModel::GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
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

ESlateVisibility UFriendListViewModel::GetNextVisibility(const ESlateVisibility& InVisibility)
{
	switch (InVisibility)
	{
		case ESlateVisibility::Collapsed:
			return ESlateVisibility::Visible;
		default:
			return ESlateVisibility::Collapsed;
	}
}
