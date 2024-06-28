// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/CPBeetPart.h"

ACPBeetPart::ACPBeetPart()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/UltimateFarming/Meshes/SM_Beet.SM_Beet"));
	if (MeshRef.Object) {
		MeshComponent->SetStaticMesh(MeshRef.Object);
	}

	bRetriggerable = true;

	Size = 25;
}

bool ACPBeetPart::OnTriggered()
{
	return Super::OnTriggered();


}
