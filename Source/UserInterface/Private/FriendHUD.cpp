// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendHUD.h"
#include "FriendSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AFriendHUD::AFriendHUD()
{
}

void AFriendHUD::BeginPlay()
{
	Super::BeginPlay();
	CreateAndInitializeWidget();
}

void AFriendHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (FriendListWidget)
	{
		FriendListWidget->RemoveFromParent();
		FriendListWidget = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void AFriendHUD::ShowFriendList() const
{
	if (FriendListWidget)
	{
		FriendListWidget->AddToViewport();
	}
}

void AFriendHUD::HideFriendList() const
{
	if (FriendListWidget)
	{
		FriendListWidget->RemoveFromParent();
	}
}

void AFriendHUD::ToggleFriendList() const
{
	if (FriendListWidget && FriendListWidget->IsInViewport())
	{
		HideFriendList();
	}
	else
	{
		ShowFriendList();
	}
}

TScriptInterface<IFriendService> AFriendHUD::GetFriendService() const
{
	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		UGameInstanceSubsystem*          Subsystem { GameInstance->GetSubsystemBase(FriendSubsystemClass) };
		TScriptInterface<IFriendService> Interface;
		Interface.SetObject(Subsystem);
		Interface.SetInterface(Cast<IFriendService>(Subsystem));

		return Interface;
	}

	return TScriptInterface<IFriendService>();
}

void AFriendHUD::OnFriendListWidgetCreated_Implementation()
{
	// Blueprint implementable event for additional setup
}

void AFriendHUD::CreateAndInitializeWidget()
{
	if (!FriendListWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("FriendListWidgetClass not set in HUD"));

		return;
	}

	FriendListWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), FriendListWidgetClass);

	if (FriendListWidget)
	{
		OnFriendListWidgetCreated();

		ShowFriendList();
	}
}
