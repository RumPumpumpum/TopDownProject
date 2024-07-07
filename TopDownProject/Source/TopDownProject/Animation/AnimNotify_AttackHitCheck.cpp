// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/TDAttackAnimationInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ITDAttackAnimationInterface* AttackPawn = Cast<ITDAttackAnimationInterface>(MeshComp->GetOwner());
		
		// �ش� Owner�� Interface�� �����ߴٸ� null�� �ƴ� ���� ��
		if (AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
