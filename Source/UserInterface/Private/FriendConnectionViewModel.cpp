// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendConnectionViewModel.h"

UFriendConnectionViewModel::UFriendConnectionViewModel()
	: UserID("")
	, Nickname("")
	, Level(1)
	, bIsConnected(false)
	, LastSeen("")
	, StatusMessage("")
{
}

void UFriendConnectionViewModel::SetUserID(const FString& InUserID)
{
	UE_MVVM_SET_PROPERTY_VALUE(UserID, InUserID);
}

void UFriendConnectionViewModel::SetNickname(const FString& InNickname)
{
	UE_MVVM_SET_PROPERTY_VALUE(Nickname, InNickname);
}

void UFriendConnectionViewModel::SetLevel(const int32 InLevel)
{
	UE_MVVM_SET_PROPERTY_VALUE(Level, InLevel);
}

void UFriendConnectionViewModel::SetIsConnected(const bool InIsConnected)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsConnected, InIsConnected))
	{
		SetLastSeen(InIsConnected ? TEXT("Now") : FDateTime::Now().ToString());
		SetStatusMessage(InIsConnected ? TEXT("Online") : TEXT("Offline"));
	}
}

void UFriendConnectionViewModel::SetLastSeen(const FString& InLastSeen)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastSeen, InLastSeen);
}

void UFriendConnectionViewModel::SetStatusMessage(const FString& InStatusMessage)
{
	UE_MVVM_SET_PROPERTY_VALUE(StatusMessage, InStatusMessage);
}

const FString& UFriendConnectionViewModel::GetUserID() const
{
	return UserID;
}

const FString& UFriendConnectionViewModel::GetNickname() const
{
	return Nickname;
}

int32 UFriendConnectionViewModel::GetLevel() const
{
	return Level;
}

bool UFriendConnectionViewModel::GetIsConnected() const
{
	return bIsConnected;
}

const FString& UFriendConnectionViewModel::GetLastSeen() const
{
	return LastSeen;
}

const FString& UFriendConnectionViewModel::GetStatusMessage() const
{
	return StatusMessage;
}

void UFriendConnectionViewModel::UpdateFromFriendData(const FFriendConnectionData& FriendData)
{
	SetUserID(FriendData.UserID);
	SetNickname(FriendData.Nickname);
	SetLevel(FriendData.Level);
	SetIsConnected(FriendData.bIsConnected);
	SetLastSeen(FriendData.LastSeen);
	SetStatusMessage(FriendData.StatusMessage);
}
