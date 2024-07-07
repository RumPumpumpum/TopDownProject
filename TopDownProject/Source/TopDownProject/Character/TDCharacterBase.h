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

// 기본공격
protected:
	// 블루프린트에서 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation);
	TObjectPtr<class UAnimMontage> AttackMontage;

	void AttackStart();
	void AttackEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	bool bIsAttacking = false;

// 공격 판정
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ATDElfArrowProjectile> ElfArrowProjectile;

	virtual void AttackHitCheck() override;
};
