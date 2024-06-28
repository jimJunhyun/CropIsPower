// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPCottonPart.h"
#include "CPCottonPart.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CPPlayerCharacter.h"

ACPCottonPart::ACPCottonPart()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/UltimateFarming/Meshes/SM_Cotton.SM_Cotton"));
	if (MeshRef.Object) {
		MeshComponent->SetStaticMesh(MeshRef.Object);
	}

	bRetriggerable = true;
	Size = 7;
}

bool ACPCottonPart::OnTriggered()
{
	bool Hit = Super::OnTriggered();
	if (Hit) {
		ACPPlayerCharacter* PC = Cast<ACPPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PC) {
			PC->Heal(3);
		}
	}
	return Hit;
}
