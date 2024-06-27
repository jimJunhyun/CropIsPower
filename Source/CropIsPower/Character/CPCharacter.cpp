// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACPCharacter::ACPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(21, 87);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 150;
	GetCharacterMovement()->MinAnalogWalkSpeed = 10;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	GetMesh()->SetRelativeScale3D(FVector(0.65, 0.65,0.65));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMeshRef(TEXT("/Game/CropIsPower/Models/SKM_Quinn.SKM_Quinn"));
	if (PlayerMeshRef.Object) {
		GetMesh()->SetSkeletalMesh(PlayerMeshRef.Object);
	}

}

// Called when the game starts or when spawned
void ACPCharacter::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);
}

// Called every frame
void ACPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACPCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DecreaseHp(DamageAmount);
	return DamageAmount;
}

void ACPCharacter::DecreaseHp(uint32 Amt)
{
	Hp -= Amt;
	if (Hp <= 0) {
		OnDead();
	}
}

void ACPCharacter::OnDead()
{
	UE_LOG(LogTemp, Log, TEXT("ав╬З╬Н..!"));
	Destroy();
}

void ACPCharacter::DoAttack()
{

}

void ACPCharacter::Trigger()
{

}

