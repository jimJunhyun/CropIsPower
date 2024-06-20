// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPPlayerAnimInst.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCPPlayerAnimInst::UCPPlayerAnimInst()
{
	MovingThreshold = 1;
}

void UCPPlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner) {
		Movement = Owner->GetCharacterMovement();
	}
}

void UCPPlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement) {
		MoveVel = Movement->Velocity;
		UE_LOG(LogTemp, Log, TEXT("Vel : %f, %f"), MoveVel.X, MoveVel.Y);
		bIsIdle = MoveVel.Size() < MovingThreshold;
	}
}
