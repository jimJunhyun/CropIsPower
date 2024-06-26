// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPEnemyAI.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "Character/CPPlayerCharacter.h"


ACPEnemyAI::ACPEnemyAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/CropIsPower/AI/CPEnemyBB.CPEnemyBB"));
	if (BBAssetRef.Object) {
		BBoard = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/CropIsPower/AI/CPEnemyBT.CPEnemyBT"));
	if (BTAssetRef.Object) {
		Tree = BTAssetRef.Object;
	}
}

void ACPEnemyAI::RunAI()
{
	UBlackboardComponent* BBPtr = Blackboard.Get();
	if (UseBlackboard(BBoard, BBPtr)) {
		ACPPlayerCharacter* Player = Cast<ACPPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Blackboard->SetValueAsObject(TEXT("Target"), Player);
		Blackboard->SetValueAsVector(TEXT("TargetPos"), Player->GetActorLocation());

		bool RunRes = RunBehaviorTree(Tree);
		ensure(RunRes);
	}
}

void ACPEnemyAI::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp) {
		BTComp->StopTree();
	}
}

void ACPEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
