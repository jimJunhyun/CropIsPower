// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CPBasePart.h"
#include "CPCabbagePart.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPCabbagePart : public ACPBasePart
{
	GENERATED_BODY()
public:
	ACPCabbagePart();

	virtual bool OnTriggered() override;
};
