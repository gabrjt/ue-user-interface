#pragma once

#include "CoreMinimal.h"
#include "FriendService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendSubsystem.generated.h"

class UDataTable;
struct FFriendData;
struct FStreamableHandle;

UCLASS(BlueprintType, Config=Game)
class USERINTERFACE_API UFriendSubsystem : public UGameInstanceSubsystem, public IFriendService
{
	GENERATED_BODY()

	UPROPERTY(Config)
	FSoftObjectPath FriendsDataTablePath;

	UPROPERTY(Transient)
	TArray<FFriendData> Friends;

	FOnFriendsLoaded OnFriendsLoaded;

	FOnFriendUpdated OnFriendUpdated;

public:
	UFriendSubsystem();

	UPROPERTY(BlueprintAssignable, Category = "Friends")
	FOnFriendUpdatedDelegateDynamic OnFriendUpdatedBP {};

	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	// IFriendConnectionService interface
	virtual void SubscribeOnFriendsLoaded(const FOnFriendsLoaded& Callback) override;

	virtual void UnsubscribeOnFriendsLoaded() override;

	virtual void SubscribeOnFriendUpdated(const FOnFriendUpdated& Callback) override;

	virtual void UnsubscribeOnFriendUpdated() override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void LoadFriends_Implementation() override;

	virtual bool GetFriend_Implementation(const FString& UserID, FFriendData& OutFriend) const override;

	virtual TArray<FFriendData> GetFriends_Implementation() const override;

	virtual const TArray<FFriendData>& GetFriendsRef() const override;

	virtual TArray<FFriendData> GetConnectedFriends_Implementation() const override;

	virtual TArray<FFriendData> GetDisconnectedFriends_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void UpdateFriend_Implementation(const FFriendData& InFriend) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void SetFriendIsConnected_Implementation(const FString& UserID, const bool bIsConnected) override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	virtual void RemoveFriend_Implementation(const FString& UserID) override;

	// Public API
	TSharedPtr<FStreamableHandle> LoadFriendsAsync();

	void LoadFriends(const UDataTable* DataTable);

private:
	void OnFriendsDataTableLoaded();

	void UpdateFriend(const int Index, const TFunction<void(FFriendData&)>& UpdateFunction);
};
