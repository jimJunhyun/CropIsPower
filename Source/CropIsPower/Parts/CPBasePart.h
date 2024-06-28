// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/EquipablePart.h"
#include "CPBasePart.generated.h"

UENUM()
enum class ESocketDirection : uint8 {
	Up,
	Down,
	Right,
	Left,
	Front,
	Back,
};

UCLASS()
class CROPISPOWER_API ACPBasePart : public AActor, public IEquipablePart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPBasePart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visuals)
	TObjectPtr<class UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visuals)
	TObjectPtr<class UStaticMesh> Mesh;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Connecteds)
	TMap<FString, TObjectPtr<ACPBasePart>> SocketDatas;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool OnTriggered() override;
	virtual void AddTriggerCount() override;
	virtual uint8 ConnectPart(FString SocketName, ACPBasePart* Con);

	FORCEINLINE uint8 GetTriggerCount() { return TriggerCount; }
	FORCEINLINE bool IsTriggerable() { return !bTriggeredOnce || bRetriggerable; }
	FORCEINLINE uint8 GetRetriggerable() { return bRetriggerable; }
	FORCEINLINE void SetRetriggerable(uint8 value) { bRetriggerable = value; }
protected:
	uint8 TriggerCount;
	uint8 bRetriggerable; //일회용이 아닌가??
	uint8 bTriggeredOnce;

	UPROPERTY(VisibleAnywhere, Category = Part)
	float Size;

	UPROPERTY(VisibleAnywhere, Category = Part)
	uint32 Damage;
};
