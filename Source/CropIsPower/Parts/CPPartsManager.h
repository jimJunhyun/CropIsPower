// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPartsManager.generated.h"

UCLASS()
class CROPISPOWER_API ACPPartsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPartsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void ConnectTest();
	void TriggerHolder();

	void CheckTriggers();

	FORCEINLINE class ACPBasePart* GetWeaponHolder() { return WeaponHolder; }

protected:
	UPROPERTY(VisibleAnywhere, Category = Holder)
	TObjectPtr<class ACPBasePart> WeaponHolder;

	UPROPERTY(VisibleAnywhere, Category = Holder)
	TObjectPtr<class ACPBasePart> Selected;

	FTimerHandle InvokeTimer;

	
	uint8 bTriggering;


private:
	float InvokeDelay;
};
