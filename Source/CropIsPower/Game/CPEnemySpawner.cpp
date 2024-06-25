// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPEnemySpawner.h"
#include "Character/CPEnemyCharacter.h"

// Sets default values
ACPEnemySpawner::ACPEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Enemy = ACPEnemyCharacter::StaticClass();
}

// Called when the game starts or when spawned
void ACPEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this,  &ACPEnemySpawner::DoSpawn, 0.5f, true);
}

void ACPEnemySpawner::DoSpawn()
{
	//25*25 범위 안에서 하나 생성하기 하하
	FVector SpLoc;
	FRotator SpRot;
	GetWorld()->SpawnActor<ACPEnemyCharacter>(Enemy, SpLoc, SpRot);
}


