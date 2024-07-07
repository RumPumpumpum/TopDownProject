// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TDGameMode.h"
#include "TDGameMode.h"

ATDGameMode::ATDGameMode()
{
	// �⺻ ���Ӹ�� ����

	// ����Ʈ ��
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(
		TEXT("/Game/Character/BP_TDCharacterPlayerElf.BP_TDCharacterPlayerElf_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// �÷��̾� ��Ʈ�ѷ�
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(
		TEXT("/Script/TopDownProject.TDPlayerController"));
	if(PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}


}
