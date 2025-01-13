// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendHUD.h"
#include "FriendManager.h"
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

void AFriendHUD::ShowFriendList()
{
	if (FriendListWidget)
	{
		FriendListWidget->AddToViewport();
	}
}

void AFriendHUD::HideFriendList()
{
	if (FriendListWidget)
	{
		FriendListWidget->RemoveFromParent();
	}
}

void AFriendHUD::ToggleFriendList()
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

void AFriendHUD::OnFriendListWidgetCreated_Implementation()
{
	// Blueprint implementable event for additional setup
}

IFriendService* AFriendHUD::GetFriendService() const
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		return CastChecked<IFriendService>(GameInstance->GetSubsystemBase(FriendSubsystemClass));
	}

	return nullptr;
}

void AFriendHUD::CreateAndInitializeWidget()
{
	if (!FriendListWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("FriendListWidgetClass not set in HUD"));
		return;
	}

	// Create the widget
	FriendListWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), FriendListWidgetClass);

	if (FriendListWidget)
	{
		OnFriendListWidgetCreated();

		// Initially show the widget - can be changed based on your needs
		ShowFriendList();
	}
}
