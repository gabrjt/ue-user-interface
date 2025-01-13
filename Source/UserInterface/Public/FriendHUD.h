// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FriendHUD.generated.h"

class UFriendListViewModel;
class UUserWidget;
class IFriendService;

UCLASS()
class USERINTERFACE_API AFriendHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Friends")
	TSubclassOf<UGameInstanceSubsystem> FriendSubsystemClass {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> FriendListWidgetClass {};

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* FriendListWidget {};

public:
	AFriendHUD();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Friends | UI")
	void ShowFriendList() const;

	UFUNCTION(BlueprintCallable, Category = "Friends | UI")
	void HideFriendList() const;

	UFUNCTION(BlueprintCallable, Category = "Friends | UI")
	void ToggleFriendList() const;

	UFUNCTION(BlueprintCallable, Category = "Friends")
	TScriptInterface<IFriendService> GetFriendService() const;

protected:
	// Called when the widget is created - can be overridden in Blueprint to do additional setup
	UFUNCTION(BlueprintNativeEvent, Category = "Friends | UI")
	void OnFriendListWidgetCreated();

	virtual void OnFriendListWidgetCreated_Implementation();

private:
	void CreateAndInitializeWidget();
};
