#include "FriendManager.h"
#include "Engine/GameInstance.h"
#include "Misc/AutomationTest.h"

// Helper class for friend manager tests to share setup code
class FFriendManagerTestHelper
{
public:
	UGameInstance*  GameInstance {};
	UFriendManager* FriendManager {};

	FFriendManagerTestHelper()
		: GameInstance(NewObject<UGameInstance>())
	{
		GameInstance->Init();
		FriendManager = GameInstance->GetSubsystem<UFriendManager>();
	}

	~FFriendManagerTestHelper()
	{
		GameInstance->Shutdown();
		GameInstance  = nullptr;
		FriendManager = nullptr;
	}

	// Helper method for creating test friend data
	static FFriendData CreateTestFriend(const FString& UserId, const FString& Nickname = TEXT("Test User"), bool bIsConnected = false)
	{
		return { UserId, Nickname, bIsConnected };
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerAddTest,
	"UserProject.Editor.FriendManager.AddFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerAddTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;

	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1"));

	const TArray Friends { Helper.FriendManager->GetFriends() };

	TestEqual("Friend was added successfully", Friends.Num(), 1);
	TestEqual("Added friend has correct ID", Friends[0].UserID, "TestUser1");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerConnectionTest,
	"UserProject.Editor.FriendManager.ConnectionStatus",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerConnectionTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;
	FFriendData                    Friend;

	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1"));
	Helper.FriendManager->SetFriendIsConnected("TestUser1", true);

	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Friend is online now", Friend.LastSeen, "Online Now");
	TestEqual("Connected friends count is correct", Helper.FriendManager->GetConnectedFriends().Num(), 1);
	TestEqual("Disconnected friends count is correct", Helper.FriendManager->GetDisconnectedFriends().Num(), 0);

	Helper.FriendManager->SetFriendIsConnected("TestUser1", false);

	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Friend last seen now", Friend.LastSeen, FDateTime::Now().ToString());
	TestEqual("Connected friends count is correct", Helper.FriendManager->GetConnectedFriends().Num(), 0);
	TestEqual("Disconnected friends count is correct", Helper.FriendManager->GetDisconnectedFriends().Num(), 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerNotificationTest,
	"UserProject.Editor.FriendManager.UpdateNotification",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerNotificationTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;
	bool                           bNotificationReceived = false;
	FOnFriendUpdatedDelegate       UpdateDelegate;

	UpdateDelegate.BindLambda([&bNotificationReceived](const FFriendData& UpdatedFriend)
	{
		bNotificationReceived = true;
	});

	const FDelegateHandle DelegateHandle = Helper.FriendManager->SubscribeOnFriendUpdated(UpdateDelegate);

	FFriendData Friend { Helper.CreateTestFriend("TestUser1", "Original Name") };
	Helper.FriendManager->AddFriend(Friend);

	Friend.Nickname = "Updated Name";
	Helper.FriendManager->UpdateFriend(Friend);

	TestTrue("Update notification was received", bNotificationReceived);
	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Updated Name");

	Helper.FriendManager->UnsubscribeOnFriendUpdated(DelegateHandle);
	bNotificationReceived = false;
	Friend.Nickname       = "Another Name";
	Helper.FriendManager->UpdateFriend(Friend);

	TestFalse("Update notification was not received", bNotificationReceived);
	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Another Name");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerRemovalTest,
	"UserProject.Editor.FriendManager.RemoveFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerRemovalTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;

	// Add a test friend
	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendManager->GetFriends().Num(), 1);

	// Remove the friend
	Helper.FriendManager->RemoveFriend("TestUser1");

	TestEqual("All friends list is empty after removal",
		Helper.FriendManager->GetFriends().Num() + Helper.FriendManager->GetConnectedFriends().Num() + Helper.FriendManager->GetDisconnectedFriends().Num(),
		0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerDuplicateTest,
	"UserProject.Editor.FriendManager.DuplicateFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerDuplicateTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;
	FFriendData                    Friend;

	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendManager->GetFriends().Num(), 1);
	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Nickname is default", Friend.Nickname, "Test User");

	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1", "I'm the same"));

	TestEqual("Friend was not added", Helper.FriendManager->GetFriends().Num(), 1);
	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "I'm the same");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerNonexistentTest,
	"UserProject.Editor.FriendManager.NonexistentFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerNonexistentTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;
	FFriendData                    Friend;

	Helper.FriendManager->AddFriend(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendManager->GetFriends().Num(), 1);
	TestTrue("Found Friend", Helper.FriendManager->GetFriend("TestUser1", Friend));

	Helper.FriendManager->RemoveFriend("TestUser2");

	TestEqual("Friend was not removed", Helper.FriendManager->GetFriends().Num(), 1);
	TestFalse("Friend not found", Helper.FriendManager->GetFriend("TestUser2", Friend));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerLoadTest,
	"UserProject.Editor.FriendManager.LoadFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerLoadTest::RunTest(const FString& Parameters)
{
	const FFriendManagerTestHelper Helper;

	// Create a test DataTable
	UDataTable* FriendsTable { NewObject<UDataTable>() };
	FriendsTable->RowStruct = FFriendData::StaticStruct();

	// Add test rows to the DataTable
	FriendsTable->AddRow(FName("Row1"), Helper.CreateTestFriend("TestUser1", "User One"));
	FriendsTable->AddRow(FName("Row2"), Helper.CreateTestFriend("TestUser2", "User Two", true));

	// Load friends from the DataTable
	Helper.FriendManager->LoadFriends(FriendsTable);

	// Verify friends were loaded correctly
	const TArray<FFriendData>& LoadedFriends = Helper.FriendManager->GetFriends();
	TestEqual("Correct number of friends loaded", LoadedFriends.Num(), 2);

	FFriendData Friend1, Friend2;
	TestTrue("Found first friend", Helper.FriendManager->GetFriend("TestUser1", Friend1));
	TestTrue("Found second friend", Helper.FriendManager->GetFriend("TestUser2", Friend2));

	TestEqual("First friend nickname correct", Friend1.Nickname, "User One");
	TestEqual("Second friend nickname correct", Friend2.Nickname, "User Two");
	TestEqual("Second friend connection status correct", Friend2.bIsConnected, true);

	// Test updating existing friend via LoadFriends
	UDataTable* UpdateTable { NewObject<UDataTable>() };
	UpdateTable->RowStruct = FFriendData::StaticStruct();
	UpdateTable->AddRow(FName("UpdateRow"), Helper.CreateTestFriend("TestUser1", "Updated User"));

	Helper.FriendManager->LoadFriends(UpdateTable);

	TestTrue("Found updated friend", Helper.FriendManager->GetFriend("TestUser1", Friend1));
	TestEqual("Nickname was updated", Friend1.Nickname, "Updated User");
	TestEqual("Friend count unchanged", Helper.FriendManager->GetFriends().Num(), 2);

	// Test with invalid DataTable
	Helper.FriendManager->LoadFriends(nullptr);
	TestEqual("Friends list unchanged with null DataTable", Helper.FriendManager->GetFriends().Num(), 2);

	return true;
}
