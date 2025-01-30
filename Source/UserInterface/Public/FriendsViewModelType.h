#pragma once

#include "CoreMinimal.h"
#include "FriendsViewModelType.generated.h"

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EFriendsViewModelType : uint8
{
	Connected    = 0x01,
	Disconnected = 0x02,
};

ENUM_CLASS_FLAGS(EFriendsViewModelType);
