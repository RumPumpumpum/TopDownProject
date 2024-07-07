// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/TDAttackAnimationInterface.h"
#include "Projectile/TDElfArrowProjectile.h"
#include "TDCharacterBase.generated.h"

UCLASS()
class TOPDOWNPROJECT_API ATDCharacterBase : public ACharacter, public ITDAttackAnimationInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDCharacterBase();

// �⺻����
protected:
	// �������Ʈ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation);
	TObjectPtr<class UAnimMontage> AttackMontage;

	void AttackStart();
	void AttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	bool bIsAttacking = false;

// ���� ����
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ATDElfArrowProjectile> ElfArrowProjectile;

	virtual void AttackHitCheck() override;
};
