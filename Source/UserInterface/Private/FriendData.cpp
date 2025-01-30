#include "FriendData.h"

FFriendData::FFriendData()
	: UserID()
	, Nickname()
	, Level(-1)
	, bIsConnected(false)
	, LastSeen()
	, StatusMessage() {}

FFriendData::FFriendData(const FString& UserID, const FString& Nickname, const bool bIsConnected)
	: UserID(UserID)
	, Nickname(Nickname)
	, Level(1)
	, bIsConnected(bIsConnected)
	, LastSeen(GetLastSeen(bIsConnected))
	, StatusMessage("Away") {}

FString FFriendData::GetLastSeen(const bool bIsConnected)
{
	return bIsConnected ? TEXT("Now") : FDateTime::Now().ToString();
}

bool FFriendData::operator==(const FString& InUserID) const
{
	return UserID == InUserID;
}

bool FFriendData::operator==(const FFriendData& Other) const
{
	return operator==(Other.UserID);
}
