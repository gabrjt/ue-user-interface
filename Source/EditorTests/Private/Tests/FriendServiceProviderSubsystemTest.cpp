﻿#include "FriendServiceProviderSubsystem.h"
#include "FriendSubsystem.h"
#include "SubsystemTestHelper.h"

class FFriendServiceProviderSubsystemTestHelper : public TSubsystemTestHelper<UFriendServiceProviderSubsystem> {};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFriendServiceProviderSubsystemGetInterfaceTest,
	"UserProject.Editor.FriendServiceProviderSubsystem.GetInterface",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FFriendServiceProviderSubsystemGetInterfaceTest::RunTest(const FString& Parameters)
{
	const FFriendServiceProviderSubsystemTestHelper Helper;
	const TScriptInterface                          Interface { Helper.Subsystem->GetFriendService() };

	TestEqual("Friend Service returned successfully",
		Interface.GetObject(),
		Cast<UObject>(Helper.GameInstance->GetSubsystem<UFriendSubsystem>()));

	return true;
}
