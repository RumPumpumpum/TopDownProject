// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDPlayerController.h"

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 게임 시작 시 마우스를 게임안에 가둠
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	
}
