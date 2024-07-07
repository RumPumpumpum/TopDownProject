// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/TDAttackAnimationInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ITDAttackAnimationInterface* AttackPawn = Cast<ITDAttackAnimationInterface>(MeshComp->GetOwner());
		
		// 해당 Owner가 Interface를 구현했다면 null이 아닌 값이 들어감
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
