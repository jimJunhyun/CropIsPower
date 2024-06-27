// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnTo.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API UBTTask_TurnTo : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TurnTo();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
