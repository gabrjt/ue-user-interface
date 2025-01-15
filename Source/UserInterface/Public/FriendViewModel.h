#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendViewModel.generated.h"

struct FFriendData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString UserID {};

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString Nickname {};

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	int32 Level {};

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter="SetIsConnected", Getter="GetIsConnected", meta=(AllowPrivateAccess))
	bool bIsConnected {};

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString LastSeen {};

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString StatusMessage {};

public:
	UFriendViewModel();

	static UFriendViewModel* Create(UObject* InOuter, const FFriendData& InFriend);

	void SetUserID(const FString& InUserID);

	void SetNickname(const FString& InNickname);

	void SetLevel(const int32 InLevel);

	void SetIsConnected(const bool bInIsConnected);

	void SetLastSeen(const FString& InLastSeen);

	void SetStatusMessage(const FString& InStatusMessage);

	const FString& GetUserID() const;

	const FString& GetNickname() const;

	int32 GetLevel() const;

	bool GetIsConnected() const;

	const FString& GetLastSeen() const;

	const FString& GetStatusMessage() const;

	UFUNCTION(BlueprintCallable)
	void Set(const FFriendData& InFriend);

	bool operator==(const FString& InUserID) const;

	bool operator==(const FFriendData& Other) const;

	bool operator==(const UFriendViewModel& Other) const;
};
