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
	return Visibility;
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
	switch (Visibility)
	{
		case ESlateVisibility::Collapsed:
			SetVisibilityAndText(ESlateVisibility::Visible);

			break;

		default:
			SetVisibilityAndText(ESlateVisibility::Collapsed);
	}
}

int UFriendListViewModel::GetFriendsCount() const
{
	return Friends.Num();
}

void UFriendListViewModel::Set(const UFriendListViewModelDataAsset* DataAsset)
{
	SetTitle(DataAsset->Title);
	SetTextColor(DataAsset->TextColor);
	SetVisibilityAndText(DataAsset->Visibility);
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
