#pragma once

template <typename TSubsystemType>
class TSubsystemTestHelper
{
public:
	UWorld*         World;
	UGameInstance*  GameInstance;
	TSubsystemType* Subsystem;

	TSubsystemTestHelper()
		: World(UWorld::CreateWorld(EWorldType::Game, true))
		, GameInstance(NewObject<UGameInstance>(World))
	{
		World->SetGameInstance(GameInstance);
		GameInstance->Init();
		Subsystem = GameInstance->GetSubsystem<TSubsystemType>();
	}

protected:
	~TSubsystemTestHelper()
	{
		GameInstance->Shutdown();
		World->DestroyWorld(true);
		World        = nullptr;
		GameInstance = nullptr;
		Subsystem    = nullptr;
	}
};
