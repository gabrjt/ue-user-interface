// FriendServiceProviderSubsystem.cpp
#include "FriendServiceProviderSubsystem.h"
#include "FriendSubsystem.h"

void UFriendServiceProviderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SetFriendServiceImplementation(FriendServiceClass);
}

void UFriendServiceProviderSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TScriptInterface<IFriendService> UFriendServiceProviderSubsystem::GetFriendService() const
{
	const UGameInstance*    GameInstance { GetGameInstance() };
	UGameInstanceSubsystem* Subsystem { GameInstance->GetSubsystemBase(FriendServiceClass.ResolveClass()) };

	TScriptInterface<IFriendService> Interface;
	Interface.SetObject(Subsystem);
	Interface.SetInterface(CastChecked<IFriendService>(Subsystem));

	return Interface;
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
