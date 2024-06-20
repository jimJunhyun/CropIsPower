// Fill out your copyright notice in the Description page of Project Settings.

#include "Parts/CPPartsManager.h"
#include "CPBasePart.h"
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
		ACPBasePart* Part = GetWorld()->SpawnActor<ACPBasePart>(FVector::ZeroVector, FRotator::ZeroRotator);
		if (Selected->ConnectPart(TEXT("Up"), Part)) {
			Selected = Part;
		}
	}
}

void ACPPartsManager::TriggerHolder()
{
	ensure(WeaponHolder != nullptr);
	WeaponHolder->AddTriggerCount();
}

void ACPPartsManager::CheckTriggers() //전부 돌기.
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

