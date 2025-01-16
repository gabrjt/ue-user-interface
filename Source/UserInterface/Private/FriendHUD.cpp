#include "FriendHUD.h"
#include "Blueprint/UserWidget.h"

AFriendHUD::AFriendHUD()
	: MainWidget()
	, MainWidgetClass()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFriendHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateMainWidget();
}

void AFriendHUD::CreateMainWidget()
{
	check(MainWidgetClass);
	check(!MainWidget);

	MainWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);

	if (ensure(MainWidget))
	{
		MainWidget->AddToViewport();
	}
}
