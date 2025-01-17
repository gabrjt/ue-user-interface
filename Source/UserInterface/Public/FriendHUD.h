#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FriendHUD.generated.h"

class UUserWidget;

UCLASS()
class USERINTERFACE_API AFriendHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	UUserWidget* MainWidget;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UUserWidget> MainWidgetClass;

public:
	AFriendHUD();

	virtual void BeginPlay() override;

protected:
	void CreateMainWidget();
};
