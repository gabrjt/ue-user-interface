#include "FriendsWidget.h"
#include "FriendsViewModel.h"
#include "FriendsWidgetViewModel.h"
#include "FriendsWidgetViewModelDataAsset.h"
#include "MVVMGameSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UFriendsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UFriendsWidgetViewModel* ViewModel { NewObject<UFriendsWidgetViewModel>() };

	GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection()->AddViewModelInstance({
			TSubclassOf<UFriendsWidgetViewModel>(),
			WidgetViewModelName
		},
		ViewModel);

	SetWidgetViewModel(ViewModel);

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(FriendsWidgetViewModelDataAsset,
		FStreamableDelegate::CreateUObject(this, &UFriendsWidget::OnDataAssetsLoaded));

	SetVisibility(ESlateVisibility::Hidden);
}

void UFriendsWidget::SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel)
{
	Super::SetViewModel_Implementation(InFriendsViewModel);

	InFriendsViewModel->SubscribeOnFriendsLoaded(ViewModelType);
}

void UFriendsWidget::OnDataAssetsLoaded()
{
	SetVisibility(ESlateVisibility::Visible);
	WidgetViewModelDataLoaded(FriendsWidgetViewModelDataAsset.Get());
}
