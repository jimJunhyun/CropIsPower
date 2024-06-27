// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CPCharacter.h"
#include "CPEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CROPISPOWER_API ACPEnemyCharacter : public ACPCharacter
{
	GENERATED_BODY()
	
public:
	ACPEnemyCharacter();

	virtual void DoAttack() override;
	virtual void Trigger() override;

	virtual void DecreaseHp(uint32 Amt) override;
	virtual void OnDead() override;

	void DoDie(UAnimMontage* Montage, bool IsPropEnded);

	void EndAnim(UAnimMontage* Montage, bool IsPropEnded);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> AttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> HitAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UAnimMontage> DieAnim;
};
