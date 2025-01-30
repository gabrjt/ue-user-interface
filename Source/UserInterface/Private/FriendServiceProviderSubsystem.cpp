#include "FriendServiceProviderSubsystem.h"
#include "FriendSubsystem.h"

UFriendServiceProviderSubsystem::UFriendServiceProviderSubsystem()
	: FriendServiceClass() {}

void UFriendServiceProviderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	SetFriendServiceImplementation(FriendServiceClass);
}

void UFriendServiceProviderSubsystem::Deinitialize() {}

TScriptInterface<IFriendService> UFriendServiceProviderSubsystem::GetFriendService() const
{
	const UGameInstance*    GameInstance { GetGameInstance() };
	UGameInstanceSubsystem* Subsystem { GameInstance->GetSubsystemBase(FriendServiceClass.ResolveClass()) };

	TScriptInterface<IFriendService> Interface;
	Interface.SetObject(Subsystem);
	Interface.SetInterface(CastChecked<IFriendService>(Subsystem));

	return Interface;
}

IFriendService* UFriendServiceProviderSubsystem::GetFriendServiceInterface() const
{
	const TScriptInterface Interface { GetFriendService() };

	return Interface.GetInterface();
}

void UFriendServiceProviderSubsystem::SetFriendServiceImplementation(FSoftClassPath InFriendServiceClass)
{
	if (!ensure(InFriendServiceClass.TryLoadClass<UGameInstanceSubsystem>()))
	{
		SetFriendServiceImplementation(UFriendSubsystem::StaticClass());

		return;
	}

	FriendServiceClass = InFriendServiceClass;
}
