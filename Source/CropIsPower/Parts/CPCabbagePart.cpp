// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPCabbagePart.h"

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
}
