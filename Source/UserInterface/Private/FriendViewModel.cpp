// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendViewModel.h"
#include "FriendData.h"

UFriendViewModel::UFriendViewModel()
	: UserID("")
	, Nickname("")
	, Level(1)
	, bIsConnected(false)
	, LastSeen("")
	, StatusMessage("")
{
}

void UFriendViewModel::SetUserID(const FString& InUserID)
{
	UE_MVVM_SET_PROPERTY_VALUE(UserID, InUserID);
}

void UFriendViewModel::SetNickname(const FString& InNickname)
{
	UE_MVVM_SET_PROPERTY_VALUE(Nickname, InNickname);
}

void UFriendViewModel::SetLevel(const int32 InLevel)
{
	UE_MVVM_SET_PROPERTY_VALUE(Level, InLevel);
}

void UFriendViewModel::SetIsConnected(const bool bInIsConnected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsConnected, bInIsConnected))
	{
		SetLastSeen(FFriendData::GetLastSeen(bInIsConnected));
	}
}

void UFriendViewModel::SetLastSeen(const FString& InLastSeen)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastSeen, InLastSeen);
}

void UFriendViewModel::SetStatusMessage(const FString& InStatusMessage)
{
	UE_MVVM_SET_PROPERTY_VALUE(StatusMessage, InStatusMessage);
}

const FString& UFriendViewModel::GetUserID() const
{
	return UserID;
}

const FString& UFriendViewModel::GetNickname() const
{
	return Nickname;
}

int32 UFriendViewModel::GetLevel() const
{
	return Level;
}

bool UFriendViewModel::GetIsConnected() const
{
	return bIsConnected;
}

const FString& UFriendViewModel::GetLastSeen() const
{
	return LastSeen;
}

const FString& UFriendViewModel::GetStatusMessage() const
{
	return StatusMessage;
}

void UFriendViewModel::Set(const FFriendData& InFriend)
{
	SetUserID(InFriend.UserID);
	SetNickname(InFriend.Nickname);
	SetLevel(InFriend.Level);
	SetIsConnected(InFriend.bIsConnected);
	SetLastSeen(InFriend.LastSeen);
	SetStatusMessage(InFriend.StatusMessage);
}
