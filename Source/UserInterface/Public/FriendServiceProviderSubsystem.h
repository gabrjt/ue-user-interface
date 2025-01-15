// FriendServiceProviderSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "FriendService.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FriendServiceProviderSubsystem.generated.h"

UCLASS(Config=Game)
class USERINTERFACE_API UFriendServiceProviderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Config)
	FSoftClassPath FriendServiceClass;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	TScriptInterface<IFriendService> GetFriendService() const;

	IFriendService* GetFriendServiceInterface() const;

	// Optional: Allow runtime switching of implementation
	UFUNCTION(BlueprintCallable, Category = "Friends")
	void SetFriendServiceImplementation(FSoftClassPath InFriendServiceClass);
};
