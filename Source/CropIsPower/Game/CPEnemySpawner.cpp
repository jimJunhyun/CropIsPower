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
	
	
}

void ACPEnemySpawner::DoSpawn()
{
	//5*5 범위 안에서 하나 생성하기 하하
	
}


