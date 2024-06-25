// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPEnemyAI : public AAIController
{
	GENERATED_BODY()
public:
	ACPEnemyAI();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBoard;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> Tree;
};
