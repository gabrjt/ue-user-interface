#include "FriendViewModel.h"
#include "FriendData.h"

UFriendViewModel::UFriendViewModel()
	: UserID()
	, Nickname()
	, Level(-1)
	, bIsConnected(false)
	, LastSeen()
	, StatusMessage() {}

UFriendViewModel* UFriendViewModel::Create(UObject* InOuter, const FFriendData& InFriend)
{
	UFriendViewModel* FriendViewModel = NewObject<UFriendViewModel>(InOuter);
	FriendViewModel->Set(InFriend);

	return FriendViewModel;
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
	UE_MVVM_SET_PROPERTY_VALUE(LastSeen, {"Last Seen: " + InLastSeen});
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

const FString& UFriendViewModel::GetLastSeenIfDisconnected() const
{
	static const FString None;

	return bIsConnected ? None : GetLastSeen();
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

bool UFriendViewModel::operator==(const FString& InUserID) const
{
	return UserID == InUserID;
}

bool UFriendViewModel::operator==(const FFriendData& Other) const
{
	return UserID == Other;
}

bool UFriendViewModel::operator==(const UFriendViewModel& Other) const
{
	return operator==(Other.UserID);
}
