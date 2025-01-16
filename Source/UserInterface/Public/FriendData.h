#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FriendData.generated.h"

USTRUCT(BlueprintType)
struct USERINTERFACE_API FFriendData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString UserID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString Nickname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	bool bIsConnected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString LastSeen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Friend Data")
	FString StatusMessage;

	FFriendData();

	FFriendData(const FString& UserID, const FString& Nickname, const bool bIsConnected);

	static FString GetLastSeen(bool bIsConnected);

	bool operator==(const FString& InUserID) const;

	bool operator==(const FFriendData& Other) const;
};
