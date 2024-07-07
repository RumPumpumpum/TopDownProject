// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacterBase.h"
#include "InputActionValue.h"
#include "TDCharacterPlayerElf.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNPROJECT_API ATDCharacterPlayerElf : public ATDCharacterBase
{
	GENERATED_BODY()

public:
	ATDCharacterPlayerElf();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// ī�޶�
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UCameraComponent> FollowCamera;

// ��ǲ
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr <class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess))
	TObjectPtr <class UInputAction> AttackAction;

	// ���ε� �Լ�
	void Move(const FInputActionValue& Value);
	
	void Attack(const FInputActionValue& Value);

};
