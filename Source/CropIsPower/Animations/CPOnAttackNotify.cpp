// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CPOnAttackNotify.h"
#include "Character/CPPlayerCharacter.h"

void UCPOnAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ACPPlayerCharacter* PC = Cast<ACPPlayerCharacter>(MeshComp->GetOwner());
	if (PC) {
		PC->Trigger();
	}
}
