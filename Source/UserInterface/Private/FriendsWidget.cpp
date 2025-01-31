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

	UFriendsWidgetViewModel* WidgetViewModel { NewObject<UFriendsWidgetViewModel>(this) };

	GetViewModelCollection()->AddViewModelInstance({ UFriendsWidgetViewModel::StaticClass(), WidgetViewModelName },
		WidgetViewModel);

	SetWidgetViewModel(WidgetViewModel);

	FStreamableManager& StreamableManager { UAssetManager::GetStreamableManager() };
	StreamableManager.RequestAsyncLoad(FriendsWidgetViewModelDataAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &UFriendsWidget::OnDataAssetsLoaded));

	SetVisibility(ESlateVisibility::Hidden);
}

void UFriendsWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (UMVVMViewModelCollectionObject* ViewModelCollection { GetViewModelCollection() })
	{
		ViewModelCollection->RemoveViewModel({ UFriendsViewModel::StaticClass(), WidgetViewModelName });
	}
}

void UFriendsWidget::SetViewModel_Implementation(UFriendsViewModel* InFriendsViewModel)
{
	InFriendsViewModel->SubscribeFriendsService(static_cast<EFriendsViewModelType>(ViewModelType));
}

void UFriendsWidget::OnDataAssetsLoaded()
{
	SetVisibility(ESlateVisibility::Visible);
	WidgetViewModelDataLoaded(FriendsWidgetViewModelDataAsset.Get());
}
