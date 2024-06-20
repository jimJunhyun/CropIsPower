// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CPBasePart.h"
#include "CPCottonPart.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPCottonPart : public ACPBasePart
{
	GENERATED_BODY()
	
public:
	ACPCottonPart();

	virtual void OnTriggered() override;
};
