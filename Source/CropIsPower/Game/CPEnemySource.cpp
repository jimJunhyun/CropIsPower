// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPEnemySource.h"
#include "Character/CPEnemyCharacter.h"

// Sets default values for this component's properties
UCPEnemySource::UCPEnemySource()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Enemy = ACPEnemyCharacter::StaticClass();
	// ...
}


// Called when the game starts
void UCPEnemySource::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UCPEnemySource::DoSpawn, 2.5f, true);
	
}

void UCPEnemySource::DoSpawn()
{
	FVector SpLoc = GetOwner()->GetActorLocation();
	FVector RandLoc = FVector::OneVector;
	
	RandLoc.X *= FMath::RandRange(-500.0, 500.0);
	RandLoc.Y *= FMath::RandRange(-500.0, 500.0);
	const FTransform SpTrm(FQuat::Identity, SpLoc + RandLoc);
	ACPEnemyCharacter* ECh = GetWorld()->SpawnActorDeferred<ACPEnemyCharacter>(Enemy, SpTrm);
	if (ECh) {
		ECh->FinishSpawning(SpTrm);
	}
}



