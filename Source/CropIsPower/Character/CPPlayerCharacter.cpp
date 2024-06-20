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


ACPPlayerCharacter::ACPPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250;
	SpringArm->bUsePawnControlRotation = true;

	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	PlayerCam->bUsePawnControlRotation = false;

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
	PartManager->GetWeaponHolder()->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_rSocket"));
	FVector SockLoc = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FRotator SockRot = GetMesh()->GetSocketRotation(TEXT("hand_rSocket"));
	PartManager->GetWeaponHolder()->SetActorLocation(SockLoc);
	PartManager->GetWeaponHolder()->SetActorRotation(SockRot);
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
	PartManager->ConnectTest();
	PartManager->TriggerHolder();
}
