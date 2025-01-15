#include "FriendSubsystem.h"
#include "Engine/GameInstance.h"
#include "Misc/AutomationTest.h"

class FFriendSubsystemTestHelper
{
public:
	UGameInstance*    GameInstance {};
	UFriendSubsystem* FriendSubsystem {};

	FFriendSubsystemTestHelper()
		: GameInstance(NewObject<UGameInstance>())
	{
		GameInstance->Init();
		FriendSubsystem = GameInstance->GetSubsystem<UFriendSubsystem>();
	}

	~FFriendSubsystemTestHelper()
	{
		GameInstance->Shutdown();
		GameInstance    = nullptr;
		FriendSubsystem = nullptr;
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
	const FFriendSubsystemTestHelper Helper;

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	const TArray Friends { Helper.FriendSubsystem->GetFriends_Implementation() };

	TestEqual("Friend was added successfully", Friends.Num(), 1);
	TestEqual("Added friend has correct ID", Friends[0].UserID, "TestUser1");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerConnectionTest,
	"UserProject.Editor.FriendManager.ConnectionStatus",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerConnectionTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));
	Helper.FriendSubsystem->SetFriendIsConnected_Implementation("TestUser1", true);

	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Friend is online now", Friend.LastSeen, "Now");
	TestEqual("Connected friends count is correct", Helper.FriendSubsystem->GetConnectedFriends_Implementation().Num(), 1);
	TestEqual("Disconnected friends count is correct", Helper.FriendSubsystem->GetDisconnectedFriends_Implementation().Num(), 0);

	Helper.FriendSubsystem->SetFriendIsConnected_Implementation("TestUser1", false);

	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Friend last seen now", Friend.LastSeen, FDateTime::Now().ToString());
	TestEqual("Connected friends count is correct", Helper.FriendSubsystem->GetConnectedFriends_Implementation().Num(), 0);
	TestEqual("Disconnected friends count is correct", Helper.FriendSubsystem->GetDisconnectedFriends_Implementation().Num(), 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerNotificationTest,
	"UserProject.Editor.FriendManager.UpdateNotification",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerNotificationTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	bool                             bNotificationReceived = false;
	FOnFriendUpdatedDelegate         UpdateDelegate;

	UpdateDelegate.BindLambda([&bNotificationReceived](const FFriendData& UpdatedFriend)
	{
		bNotificationReceived = true;
	});

	const FDelegateHandle DelegateHandle = Helper.FriendSubsystem->SubscribeOnFriendUpdated(UpdateDelegate);

	FFriendData Friend { Helper.CreateTestFriend("TestUser1", "Original Name") };
	Helper.FriendSubsystem->AddFriend_Implementation(Friend);

	Friend.Nickname = "Updated Name";
	Helper.FriendSubsystem->UpdateFriend_Implementation(Friend);

	TestTrue("Update notification was received", bNotificationReceived);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Updated Name");

	Helper.FriendSubsystem->UnsubscribeOnFriendUpdated(DelegateHandle);
	bNotificationReceived = false;
	Friend.Nickname       = "Another Name";
	Helper.FriendSubsystem->UpdateFriend_Implementation(Friend);

	TestFalse("Update notification was not received", bNotificationReceived);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Another Name");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerRemovalTest,
	"UserProject.Editor.FriendManager.RemoveFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerRemovalTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;

	// Add a test friend
	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);

	// Remove the friend
	Helper.FriendSubsystem->RemoveFriend_Implementation("TestUser1");

	TestEqual("All friends list is empty after removal",
		Helper.FriendSubsystem->GetFriends_Implementation().Num() + Helper.FriendSubsystem->GetConnectedFriends_Implementation().Num() + Helper.FriendSubsystem
		->GetDisconnectedFriends_Implementation().Num(),
		0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerDuplicateTest,
	"UserProject.Editor.FriendManager.DuplicateFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerDuplicateTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname is default", Friend.Nickname, "Test User");

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1", "I'm the same"));

	TestEqual("Friend was not added", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "I'm the same");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerNonexistentTest,
	"UserProject.Editor.FriendManager.NonexistentFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerNonexistentTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend));

	Helper.FriendSubsystem->RemoveFriend_Implementation("TestUser2");

	TestEqual("Friend was not removed", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);
	TestFalse("Friend not found", Helper.FriendSubsystem->GetFriend_Implementation("TestUser2", Friend));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerGetFriendTest,
	"UserProject.Editor.FriendManager.GetFriendByValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerGetFriendTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend1, Friend2;

	Helper.FriendSubsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 1);
	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend1));

	Friend1.Nickname = "New nickname";

	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend2));
	TestNotEqual("Friend was not updated", Friend1.Nickname, Friend2.Nickname);

	Helper.FriendSubsystem->UpdateFriend_Implementation(Friend1);

	TestTrue("Found Friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend2));
	TestEqual("Friend was updated", Friend1.Nickname, Friend2.Nickname);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendManagerLoadTest,
	"UserProject.Editor.FriendManager.LoadFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendManagerLoadTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;

	// Create a test DataTable
	UDataTable* FriendsTable { NewObject<UDataTable>() };
	FriendsTable->RowStruct = FFriendData::StaticStruct();

	// Add test rows to the DataTable
	FriendsTable->AddRow(FName("Row1"), Helper.CreateTestFriend("TestUser1", "User One"));
	FriendsTable->AddRow(FName("Row2"), Helper.CreateTestFriend("TestUser2", "User Two", true));

	// Load friends from the DataTable
	Helper.FriendSubsystem->LoadFriends(FriendsTable);

	// Verify friends were loaded correctly
	const TArray<FFriendData>& LoadedFriends = Helper.FriendSubsystem->GetFriends_Implementation();
	TestEqual("Correct number of friends loaded", LoadedFriends.Num(), 2);

	FFriendData Friend1, Friend2;
	TestTrue("Found first friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend1));
	TestTrue("Found second friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser2", Friend2));

	TestEqual("First friend nickname correct", Friend1.Nickname, "User One");
	TestEqual("Second friend nickname correct", Friend2.Nickname, "User Two");
	TestEqual("Second friend connection status correct", Friend2.bIsConnected, true);

	// Test updating existing friend via LoadFriends
	UDataTable* UpdateTable { NewObject<UDataTable>() };
	UpdateTable->RowStruct = FFriendData::StaticStruct();
	UpdateTable->AddRow(FName("UpdateRow"), Helper.CreateTestFriend("TestUser1", "Updated User"));

	Helper.FriendSubsystem->LoadFriends(UpdateTable);

	TestTrue("Found updated friend", Helper.FriendSubsystem->GetFriend_Implementation("TestUser1", Friend1));
	TestEqual("Nickname was updated", Friend1.Nickname, "Updated User");
	TestEqual("Friend count unchanged", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 2);

	// Test with invalid DataTable
	Helper.FriendSubsystem->LoadFriends(nullptr);
	TestEqual("Friends list unchanged with null DataTable", Helper.FriendSubsystem->GetFriends_Implementation().Num(), 2);

	return true;
}
