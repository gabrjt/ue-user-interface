#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendsNotificationsWidgetEntryViewModel.generated.h"

UCLASS(BlueprintType)
class USERINTERFACE_API UFriendsNotificationsWidgetEntryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float RenderOpacity;

public:
	UFriendsNotificationsWidgetEntryViewModel();

	void SetRenderOpacity(const float InRenderOpacity);

	float GetRenderOpacity() const;

	UFUNCTION(BlueprintCallable)
	void ResetRenderOpacity();
};
