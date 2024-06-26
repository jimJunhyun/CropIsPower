// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPEnemySource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPISPOWER_API UCPEnemySource : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UCPEnemySource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void DoSpawn();

protected:
	UPROPERTY(EditAnywhere, Category = Enemy, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACPEnemyCharacter> Enemy;

	FTimerHandle SpawnTimer;
	FRandomStream Randomizer;
};
