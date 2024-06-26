// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CPCharacter.h"
#include "InputActionValue.h"
#include "CPPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPPlayerCharacter : public ACPCharacter
{


	GENERATED_BODY()
	
public:
	ACPPlayerCharacter();

	FORCEINLINE TObjectPtr<class ACPPartsManager> GetPartsManager() { return PartManager; }
	void ObtainWeapon();
	void Trigger();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void DoMove(const FInputActionValue& val);
	void DoTurn(const FInputActionValue& val);
	void DoAttack();
	void SetNextAttack();
	void NextAttack();
	void EndAttack(class UAnimMontage* Montage, bool IsPropEnded);

protected:
	FTimerHandle ComboTimerHandle;
	uint8 bFirstAttack = true;
	uint8 bAttackCall = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> PlayerCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCPEnemySource> EnemySpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<class UInputAction> TurnAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<class UInputMappingContext> InputMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<class ACPPartsManager> PartManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> AttackAnim;
};
