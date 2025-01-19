#include "FriendListViewModel.h"
#include "FriendData.h"
#include "FriendListViewModelDataAsset.h"
#include "FriendViewModel.h"
#include "Components/SlateWrapperTypes.h"

UFriendListViewModel::UFriendListViewModel()
	: Friends()
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

const TArray<UFriendViewModel*>& UFriendListViewModel::GetFriends() const
{
	return Friends;
}

void UFriendListViewModel::RemoveFriend(const FString& UserID)
{
	if (const int32 Index {
		Friends.IndexOfByPredicate([&UserID](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == UserID;
		})
	}; Index != INDEX_NONE)
	{
		Friends.RemoveAt(Index);

		BroadcastFriends();
	}
}

void UFriendListViewModel::ClearFriends()
{
	Friends.Empty();

	BroadcastFriends();
}

void UFriendListViewModel::UpdateFriend(const FFriendData& InFriend)
{
	if (const int32 Index {
		Friends.IndexOfByPredicate([&InFriend](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == InFriend;
		})
	}; Index != INDEX_NONE)
	{
		Friends[Index]->Set(InFriend);
	}
	else
	{
		AddFriend(InFriend);
		BroadcastFriends();
	}
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
	static ESlateVisibility Visible { ESlateVisibility::Visible };

	if (IsChangingVisibility())
	{
		return Visible;
	}

	return Visibility;
}

void UFriendListViewModel::SetTargetVisibility(const ESlateVisibility& InTargetVisibility)
{
	UE_MVVM_SET_PROPERTY_VALUE(TargetVisibility, InTargetVisibility);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsChangingVisibility);
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
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsChangingVisibility);
}

int UFriendListViewModel::GetFriendsCount() const
{
	return Friends.Num();
}

bool UFriendListViewModel::IsChangingVisibility() const
{
	return Visibility != TargetVisibility;
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

const FString& UFriendListViewModel::GetVisibilityTextFromEnum(const ESlateVisibility& InVisibility)
{
	static FString Collapsed { "+" };
	static FString Visible { "-" };

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
