// Copyright Epic Games, Inc. All Rights Reserved.


#include "CropIsPowerGameModeBase.h"

ACropIsPowerGameModeBase::ACropIsPowerGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> TpsPersonRef(TEXT("/Script/CropIsPower.CPPlayerCharacter"));
	if (TpsPersonRef.Class) {
		DefaultPawnClass = TpsPersonRef.Class;
	}
}
