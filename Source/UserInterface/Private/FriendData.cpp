// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendData.h"

FFriendData::FFriendData()
	: UserID("")
	, Nickname("")
	, Level(1)
	, bIsConnected(false)
	, LastSeen(GetLastSeen(bIsConnected))
	, StatusMessage("")
{
}

FFriendData::FFriendData(const FString& UserID, const FString& Nickname, const bool bIsConnected)
	: UserID(UserID)
	, Nickname(Nickname)
	, Level(1)
	, bIsConnected(bIsConnected)
	, LastSeen(GetLastSeen(bIsConnected))
	, StatusMessage("")
{
}

FString FFriendData::GetLastSeen(bool bIsConnected)
{
	return bIsConnected ? TEXT("Online Now") : FDateTime::Now().ToString();
}
