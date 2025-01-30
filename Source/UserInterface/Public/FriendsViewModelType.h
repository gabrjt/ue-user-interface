#pragma once

#include "CoreMinimal.h"
#include "FriendsViewModelType.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EFriendsViewModelType : uint8
{
	None         = 0 UMETA(DisplayName = "None"),
	Connected    = 1 << 0 UMETA(DisplayName = "Connected"),
	Disconnected = 1 << 1 UMETA(DisplayName = "Disconnected"),
	All          = 1 << 2 UMETA(DisplayName = "All")};
