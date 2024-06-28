// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CPBasePart.h"
#include "CPBeetPart.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPBeetPart : public ACPBasePart
{
	GENERATED_BODY()
	
public:
	ACPBeetPart();

	virtual bool OnTriggered() override;
};
