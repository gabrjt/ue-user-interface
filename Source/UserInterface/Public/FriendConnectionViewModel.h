// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendConnectionViewModel.generated.h"

struct FFriendConnectionData;

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendConnectionViewModel : public UMVVMViewModelBase
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
	UFriendConnectionViewModel();

	void SetUserID(const FString& InUserID);

	void SetNickname(const FString& InNickname);

	void SetLevel(const int32 InLevel);

	void SetIsConnected(const bool InIsConnected);

	void SetLastSeen(const FString& InLastSeen);

	void SetStatusMessage(const FString& InStatusMessage);

	const FString& GetUserID() const;

	const FString& GetNickname() const;

	int32 GetLevel() const;

	bool GetIsConnected() const;

	const FString& GetLastSeen() const;

	const FString& GetStatusMessage() const;

	UFUNCTION(BlueprintCallable)
	void UpdateFromFriendData(const FFriendConnectionData& FriendData);
};
