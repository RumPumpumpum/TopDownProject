// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TDGameMode.h"
#include "TDGameMode.h"

ATDGameMode::ATDGameMode()
{
	// 기본 게임모드 설정

	// 디폴트 폰
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(
		TEXT("/Game/Character/BP_TDCharacterPlayerElf.BP_TDCharacterPlayerElf_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// 플레이어 컨트롤러
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(
		TEXT("/Script/TopDownProject.TDPlayerController"));
	if(PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}


}
