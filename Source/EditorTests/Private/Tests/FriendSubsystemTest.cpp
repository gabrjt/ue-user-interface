#include "FriendSubsystem.h"
#include "SubsystemTestHelper.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Misc/AutomationTest.h"

class FFriendSubsystemTestHelper : public TSubsystemTestHelper<UFriendSubsystem>
{
public:
	static FFriendData CreateTestFriend(const FString& UserId, const FString& Nickname = TEXT("Test User"), const bool bIsConnected = false)
	{
		return FFriendData { UserId, Nickname, bIsConnected };
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemAddTest,
	"UserProject.Editor.FriendSubsystem.AddFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemAddTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	const TArray Friends { Helper.Subsystem->GetFriendsRef() };

	TestEqual("Friend was added successfully", Friends.Num(), 1);
	TestEqual("Added friend has correct ID", Friends[0].UserID, "TestUser1");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemConnectionTest,
	"UserProject.Editor.FriendSubsystem.ConnectionStatus",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemConnectionTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));
	Helper.Subsystem->SetFriendIsConnected_Implementation("TestUser1", true);

	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Friend is online now", Friend.LastSeen, "Now");
	TestEqual("Connected friends count is correct", Helper.Subsystem->GetConnectedFriends_Implementation().Num(), 1);
	TestEqual("Disconnected friends count is correct", Helper.Subsystem->GetDisconnectedFriends_Implementation().Num(), 0);

	Helper.Subsystem->SetFriendIsConnected_Implementation("TestUser1", false);

	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Friend last seen now", Friend.LastSeen, FDateTime::Now().ToString());
	TestEqual("Connected friends count is correct", Helper.Subsystem->GetConnectedFriends_Implementation().Num(), 0);
	TestEqual("Disconnected friends count is correct", Helper.Subsystem->GetDisconnectedFriends_Implementation().Num(), 1);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemNotificationTest,
	"UserProject.Editor.FriendSubsystem.UpdateNotification",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemNotificationTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	bool                             bNotificationReceived = false;
	FOnFriendUpdated                 OnFriendUpdatedDelegate;

	OnFriendUpdatedDelegate.BindLambda([&bNotificationReceived](const FFriendData& UpdatedFriend)
	{
		bNotificationReceived = true;
	});

	Helper.Subsystem->SubscribeOnFriendUpdated(OnFriendUpdatedDelegate);

	FFriendData Friend { Helper.CreateTestFriend("TestUser1", "Original Name") };
	Helper.Subsystem->AddFriend_Implementation(Friend);

	Friend.Nickname = "Updated Name";
	Helper.Subsystem->UpdateFriend_Implementation(Friend);

	TestTrue("Update notification was received", bNotificationReceived);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Updated Name");

	Helper.Subsystem->UnsubscribeOnFriendUpdated();
	bNotificationReceived = false;
	Friend.Nickname       = "Another Name";
	Helper.Subsystem->UpdateFriend_Implementation(Friend);

	TestFalse("Update notification was not received", bNotificationReceived);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "Another Name");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemRemovalTest,
	"UserProject.Editor.FriendSubsystem.RemoveFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemRemovalTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;

	// Add a test friend
	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.Subsystem->GetFriendsRef().Num(), 1);

	// Remove the friend
	Helper.Subsystem->RemoveFriend_Implementation("TestUser1");

	TestEqual("All friends list is empty after removal",
		Helper.Subsystem->GetFriendsRef().Num() + Helper.Subsystem->GetConnectedFriends_Implementation().Num() + Helper.Subsystem->
		GetDisconnectedFriends_Implementation().Num(),
		0);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemDuplicateTest,
	"UserProject.Editor.FriendSubsystem.DuplicateFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemDuplicateTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.Subsystem->GetFriendsRef().Num(), 1);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname is default", Friend.Nickname, "Test User");

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1", "I'm the same"));

	TestEqual("Friend was not added", Helper.Subsystem->GetFriendsRef().Num(), 1);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));
	TestEqual("Nickname updated", Friend.Nickname, "I'm the same");

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemNonexistentTest,
	"UserProject.Editor.FriendSubsystem.NonexistentFriend",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemNonexistentTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend;

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.Subsystem->GetFriendsRef().Num(), 1);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend));

	Helper.Subsystem->RemoveFriend_Implementation("TestUser2");

	TestEqual("Friend was not removed", Helper.Subsystem->GetFriendsRef().Num(), 1);
	TestFalse("Friend not found", Helper.Subsystem->GetFriend_Implementation("TestUser2", Friend));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemGetFriendTest,
	"UserProject.Editor.FriendSubsystem.GetFriendByValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemGetFriendTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	FFriendData                      Friend1, Friend2;

	Helper.Subsystem->AddFriend_Implementation(Helper.CreateTestFriend("TestUser1"));

	TestEqual("Friend was added successfully", Helper.Subsystem->GetFriendsRef().Num(), 1);
	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend1));

	Friend1.Nickname = "New nickname";

	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend2));
	TestNotEqual("Friend was not updated", Friend1.Nickname, Friend2.Nickname);

	Helper.Subsystem->UpdateFriend_Implementation(Friend1);

	TestTrue("Found Friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend2));
	TestEqual("Friend was updated", Friend1.Nickname, Friend2.Nickname);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemLoadTest,
	"UserProject.Editor.FriendSubsystem.LoadFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemLoadTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;

	// Create a test DataTable
	UDataTable* FriendsTable { NewObject<UDataTable>() };
	FriendsTable->RowStruct = FFriendData::StaticStruct();

	// Add test rows to the DataTable
	FriendsTable->AddRow(FName("Row1"), Helper.CreateTestFriend("TestUser1", "User One"));
	FriendsTable->AddRow(FName("Row2"), Helper.CreateTestFriend("TestUser2", "User Two", true));

	// Load friends from the DataTable
	Helper.Subsystem->LoadFriends(FriendsTable);

	// Verify friends were loaded correctly
	const TArray<FFriendData>& LoadedFriends = Helper.Subsystem->GetFriendsRef();
	TestEqual("Correct number of friends loaded", LoadedFriends.Num(), 2);

	FFriendData Friend1, Friend2;
	TestTrue("Found first friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend1));
	TestTrue("Found second friend", Helper.Subsystem->GetFriend_Implementation("TestUser2", Friend2));

	TestEqual("First friend nickname correct", Friend1.Nickname, "User One");
	TestEqual("Second friend nickname correct", Friend2.Nickname, "User Two");
	TestEqual("Second friend connection status correct", Friend2.bIsConnected, true);

	// Test updating existing friend via LoadFriends
	UDataTable* UpdateTable { NewObject<UDataTable>() };
	UpdateTable->RowStruct = FFriendData::StaticStruct();
	UpdateTable->AddRow(FName("UpdateRow"), Helper.CreateTestFriend("TestUser1", "Updated User"));

	Helper.Subsystem->LoadFriends(UpdateTable);

	TestTrue("Found updated friend", Helper.Subsystem->GetFriend_Implementation("TestUser1", Friend1));
	TestEqual("Nickname was updated", Friend1.Nickname, "Updated User");
	TestEqual("Friend count unchanged", Helper.Subsystem->GetFriendsRef().Num(), 2);

	// Test with invalid DataTable
	Helper.Subsystem->LoadFriends(nullptr);
	TestEqual("Friends list unchanged with null DataTable", Helper.Subsystem->GetFriendsRef().Num(), 2);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendSubsystemLoadAsyncTest,
	"UserProject.Editor.FriendSubsystem.LoadFriendsAsync",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendSubsystemLoadAsyncTest::RunTest(const FString& Parameters)
{
	const FFriendSubsystemTestHelper Helper;
	TSharedPtr<FStreamableHandle>    LoadFriendsHandle = Helper.Subsystem->LoadFriendsAsync();

	ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([LoadFriendsHandle] { return LoadFriendsHandle->HasLoadCompletedOrStalled(); }));

	ADD_LATENT_AUTOMATION_COMMAND(
		FFunctionLatentCommand([this, Helper] { TestNotEqual("Loaded Friends count not equal to 0", Helper.Subsystem->GetFriendsRef().Num(), 0); return true; }
		));

	return true;
}
