// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/BTTask_DoAttack.h"
#include "Character/CPCharacter.h"
#include "AIController.h"

UBTTask_DoAttack::UBTTask_DoAttack()
{
}

EBTNodeResult::Type UBTTask_DoAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Res = Super::ExecuteTask(OwnerComp, NodeMemory);
	ACPCharacter* Char = Cast<ACPCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Char) {
		Char->DoAttack();
		return EBTNodeResult::Succeeded;
	}
	return Res;
}
