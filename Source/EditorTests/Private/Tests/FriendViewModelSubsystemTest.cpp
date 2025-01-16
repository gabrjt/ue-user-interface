#include "FriendListViewModel.h"
#include "FriendService.h"
#include "FriendSubsystem.h"
#include "FriendViewModel.h"
#include "FriendViewModelSubsystem.h"
#include "SubsystemTestHelper.h"

class FFriendViewModelSubsystemTestHelper : public TSubsystemTestHelper<UFriendViewModelSubsystem>
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendViewModelSubsystemInitializeTest,
	"UserProject.Editor.FriendViewModelSubsystem.InitializeViewModels",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendViewModelSubsystemInitializeTest::RunTest(const FString& Parameters)
{
	const FFriendViewModelSubsystemTestHelper Helper;

	TestEqual("No friends loaded yet",
		Helper.Subsystem->GetDisconnectedFriendsViewModel().GetFriends().Num() + Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends().Num(),
		0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendViewModelSubsystemPopulateViewModelsTest,
	"UserProject.Editor.FriendViewModelSubsystem.PopulateViewModels",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendViewModelSubsystemPopulateViewModelsTest::RunTest(const FString& Parameters)
{
	const FFriendViewModelSubsystemTestHelper Helper;

	Helper.LoadFriends();

	TestEqual("Disconnected Friends populated", Helper.Subsystem->GetDisconnectedFriendsViewModel().GetFriends().Num(), 1);
	TestEqual("Connected Friends populated", Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends().Num(), 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendViewModelSubsystemUpdateViewModelsTest,
	"UserProject.Editor.FriendViewModelSubsystem.UpdateViewModels",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendViewModelSubsystemUpdateViewModelsTest::RunTest(const FString& Parameters)
{
	const FFriendViewModelSubsystemTestHelper Helper;
	UFriendSubsystem*                         FriendSubsystem { Helper.GameInstance->GetSubsystem<UFriendSubsystem>() };

	Helper.LoadFriends();

	TestEqual("Disconnected Friends populated", Helper.Subsystem->GetDisconnectedFriendsViewModel().GetFriends().Num(), 1);
	TestEqual("Connected Friends populated", Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends().Num(), 1);

	FriendSubsystem->SetFriendIsConnected_Implementation("TestUser1", true);

	TestEqual("Disconnected Friends View Model updated", Helper.Subsystem->GetDisconnectedFriendsViewModel().GetFriends().Num(), 0);
	TestEqual("Connected Friends View Model updated", Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends().Num(), 2);

	FriendSubsystem->SetFriendLevel_Implementation("TestUser1", 2);
	FriendSubsystem->SetFriendLevel_Implementation("TestUser2", 3);

	const TArray<UFriendViewModel*>& ConnectedFriendsViewModels { Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends() };

	const int32 TestUser1Index {
		ConnectedFriendsViewModels.IndexOfByPredicate([](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == "TestUser1";
		})
	};

	const int32 TestUser2Index {
		ConnectedFriendsViewModels.IndexOfByPredicate([](const UFriendViewModel* Friend)
		{
			return Friend && *Friend == "TestUser2";
		})
	};

	TestNotEqual("TestUser1 Index is valid", TestUser1Index, static_cast<int32>(INDEX_NONE));
	TestNotEqual("TestUser2 Index is valid", TestUser2Index, static_cast<int32>(INDEX_NONE));
	TestNotEqual("Indexes are different", TestUser1Index, TestUser2Index);
	TestEqual("TestUser1 Level updated", ConnectedFriendsViewModels[TestUser1Index]->GetLevel(), 2);
	TestEqual("TestUser2 Level updated", ConnectedFriendsViewModels[TestUser2Index]->GetLevel(), 3);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendViewModelSubsystemViewModelsDataTest,
	"UserProject.Editor.FriendViewModelSubsystem.ViewModelsDataMatch",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendViewModelSubsystemViewModelsDataTest::RunTest(const FString& Parameters)
{
	const FFriendViewModelSubsystemTestHelper Helper;

	Helper.LoadFriends();

	const UFriendSubsystem* FriendSubsystem { Helper.GameInstance->GetSubsystem<UFriendSubsystem>() };

	const TArray<FFriendData>        ConnectedFriends = FriendSubsystem->GetConnectedFriends_Implementation();
	const TArray<UFriendViewModel*>& ConnectedFriendsViewModels { Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends() };

	TestEqual("Connected Friends count matches", ConnectedFriends.Num(), ConnectedFriendsViewModels.Num());

	for (int32 Index = 0; Index < ConnectedFriends.Num(); Index++)
	{
		const FFriendData&      Friend { ConnectedFriends[Index] };
		const UFriendViewModel* ViewModel { ConnectedFriendsViewModels[Index] };

		TestEqual("UserID matches", ViewModel->GetUserID(), Friend.UserID);
		TestEqual("Nickname matches", ViewModel->GetNickname(), Friend.Nickname);
		TestEqual("bIsConnected matches", ViewModel->GetIsConnected(), Friend.bIsConnected);
	}

	const TArray<FFriendData>        DisconnectedFriends = FriendSubsystem->GetDisconnectedFriends_Implementation();
	const TArray<UFriendViewModel*>& DisconnectedFriendsViewModels { Helper.Subsystem->GetDisconnectedFriendsViewModel().GetFriends() };

	TestEqual("Disconnected Friends count matches", DisconnectedFriends.Num(), DisconnectedFriendsViewModels.Num());

	for (int32 Index = 0; Index < DisconnectedFriends.Num(); Index++)
	{
		const FFriendData&      Friend { DisconnectedFriends[Index] };
		const UFriendViewModel* ViewModel { DisconnectedFriendsViewModels[Index] };

		TestEqual("UserID matches", ViewModel->GetUserID(), Friend.UserID);
		TestEqual("Nickname matches", ViewModel->GetNickname(), Friend.Nickname);
		TestEqual("bIsConnected matches", ViewModel->GetIsConnected(), Friend.bIsConnected);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendViewModelSubsystemViewModelDataIsUpdatedTest,
	"UserProject.Editor.FriendViewModelSubsystem.ViewModelDataIsUpdated",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendViewModelSubsystemViewModelDataIsUpdatedTest::RunTest(const FString& Parameters)
{
	const FFriendViewModelSubsystemTestHelper Helper;

	Helper.LoadFriends();

	UFriendSubsystem* FriendSubsystem { Helper.GameInstance->GetSubsystem<UFriendSubsystem>() };

	FFriendData Friend;
	FriendSubsystem->GetFriend_Implementation("TestUser2", Friend);
	Friend.Nickname = "Foo";
	FriendSubsystem->UpdateFriend_Implementation(Friend);

	const TArray<FFriendData>        ConnectedFriends = FriendSubsystem->GetConnectedFriends_Implementation();
	const TArray<UFriendViewModel*>& ConnectedFriendsViewModels { Helper.Subsystem->GetConnectedFriendsViewModel().GetFriends() };

	Friend = ConnectedFriends[0];
	const UFriendViewModel* ViewModel { ConnectedFriendsViewModels[0] };

	TestEqual("UserID matches", ViewModel->GetUserID(), Friend.UserID);
	TestEqual("Nickname matches", ViewModel->GetNickname(), Friend.Nickname);
	TestEqual("bIsConnected matches", ViewModel->GetIsConnected(), Friend.bIsConnected);
	TestEqual("Nickname updates", ViewModel->GetNickname(), "Foo");

	return true;
}
