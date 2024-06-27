// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPEnemyCharacter.h"
#include "CPEnemyAI.h"
#include "Game/CPPlayerAnimInst.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPEnemyCharacter::ACPEnemyCharacter()
{
	AIControllerClass = ACPEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	static ConstructorHelpers::FClassFinder<UCPPlayerAnimInst> Anim(TEXT("/Game/CropIsPower/Animations/ABP/CPABPEnemy.CPABPEnemy_C"));
	if (Anim.Class) {
		GetMesh()->SetAnimInstanceClass(Anim.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMon(TEXT("/Game/CropIsPower/Animations/CPEnemyAttack.CPEnemyAttack"));
	if (AttackMon.Object) {
		AttackAnim = AttackMon.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMon(TEXT("/Game/CropIsPower/Animations/CPEnemyHit.CPEnemyHit"));
	if (HitMon.Object) {
		HitAnim = HitMon.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DieMon(TEXT("/Game/CropIsPower/Animations/CPEnemyDie.CPEnemyDie"));
	if (DieMon.Object) {
		DieAnim = DieMon.Object;
	}
}

void ACPEnemyCharacter::DoAttack()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetMesh()->GetAnimInstance()->Montage_Play(AttackAnim);

	FOnMontageEnded OnEnd;
	OnEnd.BindUObject(this, &ACPEnemyCharacter::EndAnim);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, AttackAnim);
}

void ACPEnemyCharacter::Trigger()
{
	//¾Æ¸ô¶ûÆÇÁ¤¸¸µé¾î!!!!!!!!!!!!!!!!!!!!
}

void ACPEnemyCharacter::DecreaseHp(uint32 Amt)
{
	Super::DecreaseHp(Amt);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayAnimMontage(HitAnim);

	FOnMontageEnded OnEnd;
	OnEnd.BindUObject(this, &ACPEnemyCharacter::EndAnim);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, HitAnim);
}

void ACPEnemyCharacter::OnDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayAnimMontage(DieAnim);

	FOnMontageEnded OnEnd;
	OnEnd.BindUObject(this, &ACPEnemyCharacter::DoDie);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, DieAnim);
}

void ACPEnemyCharacter::DoDie(UAnimMontage* Montage, bool IsPropEnded)
{
	Super::OnDead();
}

void ACPEnemyCharacter::EndAnim(UAnimMontage* Montage, bool IsPropEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
