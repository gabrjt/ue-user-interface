#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendNotificationWidgetViewModel.generated.h"

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendNotificationWidgetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float RenderOpacity;

public:
	UFriendNotificationWidgetViewModel();

	void SetRenderOpacity(const float InRenderOpacity);

	float GetRenderOpacity() const;

	UFUNCTION(BlueprintCallable)
	void ResetRenderOpacity();
};
