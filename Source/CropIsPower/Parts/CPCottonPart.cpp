// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPCottonPart.h"
#include "CPCottonPart.h"

ACPCottonPart::ACPCottonPart()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/UltimateFarming/Meshes/SM_Cotton.SM_Cotton"));
	if (MeshRef.Object) {
		MeshComponent->SetStaticMesh(MeshRef.Object);
	}

	bRetriggerable = true;
	
}

void ACPCottonPart::OnTriggered()
{
	Super::OnTriggered();
}
