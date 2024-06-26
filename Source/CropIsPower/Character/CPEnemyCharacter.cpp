// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPEnemyCharacter.h"
#include "CPEnemyAI.h"

ACPEnemyCharacter::ACPEnemyCharacter()
{
	AIControllerClass = ACPEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	
}
