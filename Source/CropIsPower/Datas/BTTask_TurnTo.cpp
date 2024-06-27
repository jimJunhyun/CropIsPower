// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/BTTask_TurnTo.h"
#include "Character/CPCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnTo::UBTTask_TurnTo()
{
}

EBTNodeResult::Type UBTTask_TurnTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Res = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Self = OwnerComp.GetAIOwner()->GetPawn();
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (Self && Target) {
		FVector LookDir = Target->GetActorLocation() - Self->GetActorLocation();
		LookDir.Z = 0;

		FRotator TargetRot = FRotationMatrix::MakeFromX(LookDir).Rotator();
		Self->SetActorRotation(FMath::RInterpTo(Self->GetViewRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 200));

		return EBTNodeResult::Succeeded;
	}

	return Res;
}
