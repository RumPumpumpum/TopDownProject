// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/TDAttackAnimationInterface.h"
#include "Projectile/TDProjectileBase.h"
#include "Engine/DamageEvents.h"
#include "Interface/TDApplyDamageInterface.h"
#include "TDCharacterBase.generated.h"


UCLASS()
class TOPDOWNPROJECT_API ATDCharacterBase : public ACharacter, public ITDAttackAnimationInterface, public ITDApplyDamageInterface
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
	TSubclassOf<ATDProjectileBase> AttackProjectile;

	virtual void AttackHitCheck() override;

// 피격 판정
public:
	virtual void ApplyDamage(float DamageAmount, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetDead();
	void PlayDeadAnimation();
};
