#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendsNotificationsWidgetViewModel.generated.h"

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendsNotificationsWidgetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float RenderOpacity;

public:
	UFriendsNotificationsWidgetViewModel();

	void SetRenderOpacity(const float InRenderOpacity);

	float GetRenderOpacity() const;

	UFUNCTION(BlueprintCallable)
	void ResetRenderOpacity();
};
