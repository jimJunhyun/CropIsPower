// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPEnemyCharacter.h"
#include "CPEnemyAI.h"
#include "Game/CPPlayerAnimInst.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CPPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

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

	Hp = 150;
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
	TArray<FHitResult> OutHitRes;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const FVector StartPos = GetActorLocation();
	const FVector EndPos = StartPos + GetActorForwardVector() * 25;

	bool IsHit = GetWorld()->SweepMultiByChannel(OutHitRes, StartPos, EndPos, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(25), Params);
	bool PHit = false;
	if (IsHit) {
		for (auto Hits : OutHitRes)
		{
			ACPPlayerCharacter* PC = Cast<ACPPlayerCharacter>(Hits.GetActor());
			if (PC) {
				UGameplayStatics::ApplyDamage(PC, 10, GetController(), nullptr, nullptr);
				PHit = true;
			}

		}
	}

#if ENABLE_DRAW_DEBUG
	FVector Origin = StartPos + (EndPos - StartPos) * 0.5f;
	float HalfHeight = 25 * 0.5f;
	FColor Color = PHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), Origin, HalfHeight, 25, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), Color, false, 5);
#endif // ENABLE_DRAW_DEBUG
}

void ACPEnemyCharacter::DecreaseHp(int32 Amt)
{
	if (Hp > 0) {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
		if (AnimIns) {
			AnimIns->Montage_Play(HitAnim, 1);
		}
		
		FOnMontageEnded OnEnd;
		OnEnd.BindUObject(this, &ACPEnemyCharacter::EndAnim);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, HitAnim);
	}
	Super::DecreaseHp(Amt);
}

void ACPEnemyCharacter::OnDead()
{
	
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	if (AnimIns) {
		AnimIns->StopAllMontages(0);
		AnimIns->Montage_Play(DieAnim, 2);
	}
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	ACPEnemyAI* AICon = Cast<ACPEnemyAI>(GetController());
	if (AICon) {
		AICon->StopAI();
	}

	/*FOnMontageEnded OnEnd;
	OnEnd.BindUObject(this, &ACPEnemyCharacter::DoDie);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, DieAnim);*/

	FTimerHandle Dier;
	GetWorld()->GetTimerManager().SetTimer(Dier, FTimerDelegate::CreateLambda([&]() {Super::OnDead(); }), 5.0f, false);
}

void ACPEnemyCharacter::DoDie(UAnimMontage* Montage, bool IsPropEnded)
{
	Super::OnDead();
}

void ACPEnemyCharacter::EndAnim(UAnimMontage* Montage, bool IsPropEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
