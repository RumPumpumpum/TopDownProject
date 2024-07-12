// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDCharacterDummy.h"

void ATDCharacterDummy::SetDead()
{
	Super::SetDead();

	float DeadEventDelayTime = 5.0f;

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}