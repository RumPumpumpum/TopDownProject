// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*currentHp*/)


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWNPROJECT_API UTDCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTDCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetCharacterDamage() { return CharacterDamage; }
	FORCEINLINE float GetProjectileRange() { return ProjectileRange; }
	FORCEINLINE float GetProjectileSpeed() { return ProjectileSpeed; }

	FORCEINLINE void SetCharacterDamage(float NewCharacterDamage) { CharacterDamage = NewCharacterDamage; }
	FORCEINLINE void SetProjectileSpeed(float NewProjectileSpeed) { ProjectileSpeed = NewProjectileSpeed; }
	FORCEINLINE void SetProjectileRange(float NewProjectileRange) { ProjectileRange = NewProjectileRange; }
	
	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float CharacterDamage;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float ProjectileRange;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float ProjectileSpeed;
};
