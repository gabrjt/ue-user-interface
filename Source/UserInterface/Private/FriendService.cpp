#include "FriendService.h"

void IFriendService::LoadFriends_Implementation()
{
}

bool IFriendService::GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const
{
	return false;
}

TArray<FFriendData> IFriendService::GetFriends_Implementation() const
{
	return TArray<FFriendData>();
}

TArray<FFriendData> IFriendService::GetConnectedFriends_Implementation() const
{
	return TArray<FFriendData>();
}

TArray<FFriendData> IFriendService::GetDisconnectedFriends_Implementation() const
{
	return TArray<FFriendData>();
}

void IFriendService::UpdateFriend_Implementation(const FFriendData& InFriend)
{
}

void IFriendService::SetFriendIsConnected_Implementation(const FString& UserID, const bool bIsConnected)
{
}

void IFriendService::RemoveFriend_Implementation(const FString& UserID)
{
}
