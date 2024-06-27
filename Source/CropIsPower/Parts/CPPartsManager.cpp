// Fill out your copyright notice in the Description page of Project Settings.

#include "Parts/CPPartsManager.h"
#include "CPBasePart.h"
#include "CPBeetPart.h"
#include "CPCabbagePart.h"
#include "CPCottonPart.h"
#include "Character/CPPlayerCharacter.h"

// Sets default values
ACPPartsManager::ACPPartsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	InvokeDelay = 0.3f;
	bTriggering = false;
	WeaponHolder = nullptr;
	Selected = WeaponHolder;
}

// Called when the game starts or when spawned
void ACPPartsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPPartsManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("POSTINITED"));
	GetWorld()->GetTimerManager().SetTimer(InvokeTimer, this, &ACPPartsManager::CheckTriggers, InvokeDelay, true); //????????????????????
	
}

// Called every frame
//void ACPPartsManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ACPPartsManager::ConnectTest()
{
	if (WeaponHolder == nullptr) {
		WeaponHolder = GetWorld()->SpawnActor<ACPBasePart>(FVector::ZeroVector, FRotator::ZeroRotator);
		Selected = WeaponHolder;
		ACPPlayerCharacter* Player = Cast<ACPPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player) {
			Player->ObtainWeapon();
		}
	}
	else {
		uint32 R = FMath::RandRange(0, 2);
		ACPBasePart* Part = nullptr;
		switch (R)
		{
		case 0: {
			Part = GetWorld()->SpawnActor<ACPBeetPart>(FVector::ZeroVector, FRotator::ZeroRotator);
			UE_LOG(LogTemp, Log, TEXT("ºñÆ®¿¬°áµÊ"));
		}
			break;
		case 1: {

			Part = GetWorld()->SpawnActor<ACPCabbagePart>(FVector::ZeroVector, FRotator::ZeroRotator);
			UE_LOG(LogTemp, Log, TEXT("¾ç¹èÃß¿¬°áµÊ"));
		}
			break;
		case 2: {
			Part = GetWorld()->SpawnActor<ACPCottonPart>(FVector::ZeroVector, FRotator::ZeroRotator);
			UE_LOG(LogTemp, Log, TEXT("¼Ø¿¬°áµÊ"));
		}
			break;
		}
		
		if (Part != nullptr) {
			if (Selected->ConnectPart(TEXT("Up"), Part)) {
				Selected = Part;
			}
		}
	}
}

void ACPPartsManager::TriggerHolder()
{
	ensure(WeaponHolder != nullptr);
	WeaponHolder->AddTriggerCount();
}

void ACPPartsManager::CheckTriggers() //ÀüºÎ µ¹±â.
{
	if (WeaponHolder == nullptr)
		return;
	TQueue<ACPBasePart*> TriggerQueue;
	TSet<ACPBasePart*> Already;
	if (WeaponHolder->IsTriggerable() && WeaponHolder->GetTriggerCount() > 0) {
		TriggerQueue.Enqueue(WeaponHolder);
	}
	
	while(!TriggerQueue.IsEmpty())
	{
		ACPBasePart* Item;
		TriggerQueue.Dequeue(Item);
		if (Item->IsTriggerable() && Item->GetTriggerCount() > 0) {
			Item->OnTriggered();
		}
		for (auto ConnectedParts : Item->SocketDatas)
		{
			if (ConnectedParts.Value) {
				if (!Already.Contains(ConnectedParts.Value)) {
					Already.Add(ConnectedParts.Value);
					TriggerQueue.Enqueue(ConnectedParts.Value);
				}
			}
		}
	}
}

