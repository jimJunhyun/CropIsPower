// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPBasePart.h"
#include "Character/CPPlayerCharacter.h"
#include "Parts/CPPartsManager.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPBasePart::ACPBasePart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropMesh"));
	RootComponent = MeshComponent;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/UltimateFarming/Meshes/SM_Broccoli.SM_Broccoli"));
	if (MeshRef.Object) {
		MeshComponent->SetStaticMesh(MeshRef.Object);
	}

	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	bRetriggerable = true;
	
	/*SocketDatas.Add(TEXT("Up"), nullptr);
	SocketDatas.Add(TEXT("Down"), nullptr);
	SocketDatas.Add(TEXT("Right"), nullptr);
	SocketDatas.Add(TEXT("Left"), nullptr);
	SocketDatas.Add(TEXT("Front"), nullptr);
	SocketDatas.Add(TEXT("Back"), nullptr);*/
}

// Called when the game starts or when spawned
void ACPBasePart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPBasePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPBasePart::OnTriggered()
{
	
	FString Str = FString::Printf(TEXT("%s TRIGGERED!."), *(this->GetClass()->GetFName()).ToString());
	UE_LOG(LogTemp, Log, TEXT("%s"), *Str);
	
	if (!bTriggeredOnce)
		bTriggeredOnce = true;

	TArray<FHitResult> OutHitRes;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const FVector StartPos = GetActorLocation();
	const FVector EndPos = StartPos + GetActorForwardVector() * 150;

	bool IsHit = GetWorld()->SweepMultiByChannel(OutHitRes, StartPos, EndPos, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(150), Params);
	if (IsHit) {
		for (auto Hits : OutHitRes)
		{
			UGameplayStatics::ApplyDamage(Hits.GetActor(), 50, GetWorld()->GetFirstPlayerController(), nullptr, nullptr);

		}
	}

#if ENABLE_DRAW_DEBUG
	FVector Origin = StartPos + (EndPos - StartPos) * 0.5f;
	float HalfHeight = 150 * 0.5f;
	FColor Color = IsHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), Origin, HalfHeight, 150, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), Color, false, 5);
#endif // ENABLE_DRAW_DEBUG

}

void ACPBasePart::AddTriggerCount()
{
	TriggerCount += 1;
}

uint8 ACPBasePart::ConnectPart(FString SocketName, ACPBasePart* Con)
{
	
	if (!SocketDatas.Contains(SocketName)) {

		UE_LOG(LogTemp, Log, TEXT("Parameter : %s"), *SocketName);
		SocketDatas.Add(SocketName, Con);
		ACPPlayerCharacter* Player = Cast<ACPPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player) {
			
			FString SName = SocketName.Append("Socket");
			FName SocketFName = FName(*SName);
			UE_LOG(LogTemp, Log, TEXT("Name : %s"), *SName);
			if (MeshComponent->DoesSocketExist(SocketFName)) {
				Con->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketFName);
				//FVector SockLoc = MeshComponent->GetSocketLocation(SocketFName);
				//Con->SetActorRelativeLocation(SockLoc);
				//UE_LOG(LogTemp, Log, TEXT("%d, %d, %d"), SockLoc.X, SockLoc.Y, SockLoc.Z);

				return true; 
				//Con->SetActorTransform(StageTrm);
			}
			else
				return false;
		}
	}
	return false;
}

