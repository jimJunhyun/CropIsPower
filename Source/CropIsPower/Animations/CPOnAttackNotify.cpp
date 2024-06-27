// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CPOnAttackNotify.h"
#include "Character/CPCharacter.h"

void UCPOnAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ACPCharacter* PC = Cast<ACPCharacter>(MeshComp->GetOwner());
	if (PC) {
		PC->Trigger();
	}
}
