// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDPlayerController.h"

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ���� ���� �� ���콺�� ���Ӿȿ� ����
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	
}
