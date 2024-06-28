// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Parts/CPPartsManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Parts/CPBasePart.h"
#include "Game/CPPlayerAnimInst.h"
#include "Animation/AnimMontage.h"
#include "Game/CPEnemySource.h"


ACPPlayerCharacter::ACPPlayerCharacter()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250;
	SpringArm->bUsePawnControlRotation = true;

	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	PlayerCam->bUsePawnControlRotation = false;

	EnemySpawner = CreateDefaultSubobject<UCPEnemySource>(TEXT("Spawner"));
	AddOwnedComponent(EnemySpawner);

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveAct(TEXT("/Game/CropIsPower/Control/IAMove.IAMove"));
	if (MoveAct.Object) {
		MoveAction = MoveAct.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnAct(TEXT("/Game/CropIsPower/Control/IATurn.IATurn"));
	if (TurnAct.Object) {
		TurnAction = TurnAct.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttckAct(TEXT("/Game/CropIsPower/Control/IAAttack.IAAttack"));
	if (AttckAct.Object) {
		AttackAction = AttckAct.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC(TEXT("/Game/CropIsPower/Control/IMCTPS.IMCTPS"));
	if (IMC.Object) {
		InputMap = IMC.Object;
	}

	static ConstructorHelpers::FClassFinder<UCPPlayerAnimInst> Anim(TEXT("/Game/CropIsPower/Animations/ABP/CPABPPlayer.CPABPPlayer_C"));
	if (Anim.Class) {
		GetMesh()->SetAnimInstanceClass(Anim.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMon(TEXT("/Game/CropIsPower/Animations/CPAnim_Hwando_Attack_Montage.CPAnim_Hwando_Attack_Montage"));
	if (AttackMon.Object) {
		AttackAnim = AttackMon.Object;
	}

	Hp = 500;
}

void ACPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PControl = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PControl->GetLocalPlayer());
	if (System) {
		System->ClearAllMappings();
		System->AddMappingContext(InputMap, 0);
	}

	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SetRelativeRotation(FQuat::Identity);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bDoCollisionTest = true;

	bUseControllerRotationYaw = false;

	PartManager = GetWorld()->SpawnActor<ACPPartsManager>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (PartManager) {
		PartManager->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void ACPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPPlayerCharacter::DoMove);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ACPPlayerCharacter::DoTurn);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACPPlayerCharacter::DoAttack);
}



void ACPPlayerCharacter::ObtainWeapon()
{
	PartManager->GetWeaponHolder()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_rSocket"));
	FTransform SockTrm = GetMesh()->GetSocketTransform(TEXT("hand_rSocket"));
	PartManager->GetWeaponHolder()->SetActorTransform(SockTrm);
}

void ACPPlayerCharacter::Trigger()
{
	PartManager->TriggerHolder();
}

void ACPPlayerCharacter::Heal(int32 Amt)
{
	Hp += Amt;
	Hp = FMath::Clamp(Hp, 0, 1000);
}

void ACPPlayerCharacter::DoMove(const FInputActionValue& val)
{
	FVector2D MoveVec = val.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRot(0, Rotation.Yaw, 0);

	const FVector ForwardVec = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightVec = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVec, MoveVec.X);
	AddMovementInput(RightVec, MoveVec.Y);
	
	
}

void ACPPlayerCharacter::DoTurn(const FInputActionValue& val)
{
	FVector2D LookatPointVec = val.Get<FVector2D>();
	AddControllerYawInput(LookatPointVec.X);
	AddControllerPitchInput(LookatPointVec.Y);
}

void ACPPlayerCharacter::DoAttack()
{
	if (bFirstAttack) {

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		PartManager->ConnectTest();
		GetMesh()->GetAnimInstance()->Montage_Play(AttackAnim, 1.5f);
		
		FOnMontageEnded OnEnd;
		OnEnd.BindUObject(this, &ACPPlayerCharacter::EndAttack);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, AttackAnim);

		SetNextAttack();
		
		bFirstAttack = false;
		bAttackCall = false;
	}
	else {
		if (ComboTimerHandle.IsValid()) {
			bAttackCall = true;
		}
		else {

			bAttackCall = false;
		}
	}
}

void ACPPlayerCharacter::SetNextAttack()
{
	GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ACPPlayerCharacter::NextAttack, 0.91f, false);
}

void ACPPlayerCharacter::NextAttack()
{
	ComboTimerHandle.Invalidate();
	if (bAttackCall) {
		FName SectionName = *FString::Printf(TEXT("Attack%d"), (bFirstAttack ? 1: 2));
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(SectionName, AttackAnim);

		bAttackCall = false;
		
	}
}

void ACPPlayerCharacter::EndAttack(UAnimMontage* Montage, bool IsPropEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bFirstAttack = true;
	bAttackCall = false;
}
