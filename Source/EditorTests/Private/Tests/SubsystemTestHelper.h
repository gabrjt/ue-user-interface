#pragma once

template <typename TSubsystemType>
class TSubsystemTestHelper
{
public:
	UGameInstance*  GameInstance {};
	TSubsystemType* Subsystem {};

	TSubsystemTestHelper()
		: GameInstance(NewObject<UGameInstance>())
	{
		GameInstance->Init();
		Subsystem = GameInstance->GetSubsystem<TSubsystemType>();
	}

protected:
	~TSubsystemTestHelper()
	{
		GameInstance->Shutdown();
		GameInstance = nullptr;
		Subsystem    = nullptr;
	}
};
