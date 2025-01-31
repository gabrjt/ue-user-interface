#include "FriendData.h"
#include "FriendSubsystem.h"
#include "FriendsViewModel.h"
#include "FriendsViewModelType.h"
#include "MVVMGameSubsystem.h"
#include "SubsystemTestHelper.h"

class FMVVMGameSubsystemTestHelper : public TSubsystemTestHelper<UMVVMGameSubsystem>
{
public:
	void LoadFriends() const
	{
		UDataTable* FriendsTable { NewObject<UDataTable>() };
		FriendsTable->RowStruct = FFriendData::StaticStruct();
		FriendsTable->AddRow(FName("Row1"), FFriendData { "TestUser1", "User One", false });
		FriendsTable->AddRow(FName("Row2"), FFriendData { "TestUser2", "User Two", true });

		GameInstance->GetSubsystem<UFriendSubsystem>()->LoadFriends(FriendsTable);
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendsViewModelAddToCollectionTest,
	"UserProject.Editor.FriendsViewModel.AddToCollection",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendsViewModelAddToCollectionTest::RunTest(const FString& Parameters)
{
	const FMVVMGameSubsystemTestHelper Helper;

	UFriendsViewModel* ViewModel { NewObject<UFriendsViewModel>() };

	TestTrue("View Model is added to Collection",
		Helper.Subsystem->GetViewModelCollection()->AddViewModelInstance({
				UFriendsViewModel::StaticClass(),
				"ConnectedFriendsViewModel"
			},
			ViewModel));

	TestEqual("View Model is found in Collection",
		Cast<UFriendsViewModel>(
			Helper.Subsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(
				UFriendsViewModel::StaticClass())),
		ViewModel);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendsViewModelPopulate,
	"UserProject.Editor.FriendsViewModel.Populate",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendsViewModelPopulate::RunTest(const FString& Parameters)
{
	const FMVVMGameSubsystemTestHelper Helper;

	UFriendsViewModel* ConnectedFriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	ConnectedFriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Connected);

	UFriendsViewModel* DisconnectedFriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	DisconnectedFriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Disconnected);

	UFriendsViewModel* FriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	FriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Connected | EFriendsViewModelType::Disconnected);

	TestEqual("No Connected Friend is loaded yet", ConnectedFriendsViewModel->GetFriendsCount(), 0);
	TestEqual("No Disconnected Friend is loaded yet", DisconnectedFriendsViewModel->GetFriendsCount(), 0);
	TestEqual("No Friends are loaded yet", FriendsViewModel->GetFriendsCount(), 0);

	Helper.LoadFriends();

	const UFriendSubsystem* FriendSubsystem { Helper.GameInstance->GetSubsystem<UFriendSubsystem>() };

	TestEqual("Connected Friend is loaded", ConnectedFriendsViewModel->GetFriendsCount(), 1);
	TestEqual("Connected Friends are populated",
		ConnectedFriendsViewModel->GetFriendsCount(),
		FriendSubsystem->GetConnectedFriends_Implementation().Num());

	TestEqual("Disconnected Friend is loaded", DisconnectedFriendsViewModel->GetFriendsCount(), 1);
	TestEqual("Disconnected Friends are populated",
		DisconnectedFriendsViewModel->GetFriendsCount(),
		FriendSubsystem->GetDisconnectedFriends_Implementation().Num());

	TestEqual("All Friends are loaded", FriendsViewModel->GetFriendsCount(), 2);
	TestEqual("All Friends are populated", FriendsViewModel->GetFriendsCount(), FriendSubsystem->GetFriendsRef().Num());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendsViewModelUpdate,
	"UserProject.Editor.FriendsViewModel.Update",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendsViewModelUpdate::RunTest(const FString& Parameters)
{
	const FMVVMGameSubsystemTestHelper Helper;

	UFriendsViewModel* ConnectedFriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	ConnectedFriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Connected);

	UFriendsViewModel* DisconnectedFriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	DisconnectedFriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Disconnected);

	UFriendsViewModel* FriendsViewModel { NewObject<UFriendsViewModel>(Helper.World) };
	FriendsViewModel->SubscribeFriendsService(EFriendsViewModelType::Connected | EFriendsViewModelType::Disconnected);

	Helper.LoadFriends();

	UFriendSubsystem* FriendSubsystem { Helper.GameInstance->GetSubsystem<UFriendSubsystem>() };

	TestEqual("Connected Friend is initialized",
		ConnectedFriendsViewModel->GetFriends()[0]->GetUserID(),
		FriendSubsystem->GetConnectedFriends_Implementation()[0].UserID);
	TestEqual("Disconnected Friend is initialized",
		DisconnectedFriendsViewModel->GetFriends()[0]->GetUserID(),
		FriendSubsystem->GetDisconnectedFriends_Implementation()[0].UserID);
	TestEqual("All Friends are initialized",
		FriendsViewModel->GetFriends()[0]->GetUserID(),
		FriendSubsystem->GetFriendsRef()[0].UserID);
	TestEqual("All Friends are initialized",
		FriendsViewModel->GetFriends()[1]->GetUserID(),
		FriendSubsystem->GetFriendsRef()[1].UserID);

	FriendSubsystem->SetFriendLevel_Implementation(ConnectedFriendsViewModel->GetFriends()[0]->GetUserID(), 32);
	FriendSubsystem->SetFriendLevel_Implementation(DisconnectedFriendsViewModel->GetFriends()[0]->GetUserID(), 64);

	TestEqual("Connected Friend is updated", ConnectedFriendsViewModel->GetFriends()[0]->GetLevel(), 32);
	TestEqual("Connected Friend is updated",
		ConnectedFriendsViewModel->GetFriends()[0]->GetLevel(),
		FriendSubsystem->GetConnectedFriends_Implementation()[0].Level);

	TestEqual("Disconnected Friend is updated", DisconnectedFriendsViewModel->GetFriends()[0]->GetLevel(), 64);
	TestEqual("Disconnected Friend is updated",
		DisconnectedFriendsViewModel->GetFriends()[0]->GetLevel(),
		FriendSubsystem->GetDisconnectedFriends_Implementation()[0].Level);

	TestEqual("All Friends are updated", FriendsViewModel->GetFriends()[0]->GetLevel(), 64);
	TestEqual("All Friends are updated", FriendsViewModel->GetFriends()[1]->GetLevel(), 32);

	FriendSubsystem->
		SetFriendIsConnected_Implementation(ConnectedFriendsViewModel->GetFriends()[0]->GetUserID(), false);

	TestEqual("Connected Friend is updated", ConnectedFriendsViewModel->GetFriends().Num(), 0);
	TestEqual("Disconnected Friend is updated", DisconnectedFriendsViewModel->GetFriends().Num(), 2);
	TestEqual("All Friend are updated", FriendsViewModel->GetFriends().Num(), 2);

	return true;
}
