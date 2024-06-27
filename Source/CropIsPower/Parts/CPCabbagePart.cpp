// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPCabbagePart.h"
#include "Kismet/GameplayStatics.h"

ACPCabbagePart::ACPCabbagePart()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/UltimateFarming/Meshes/SM_Cabbage.SM_Cabbage"));
	if (MeshRef.Object) {
		MeshComponent->SetStaticMesh(MeshRef.Object);
	}

	bRetriggerable = true;
}

void ACPCabbagePart::OnTriggered()
{
	Super::OnTriggered();

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
