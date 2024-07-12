// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TDCharacterBase.h"
#include "TDCharacterDummy.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNPROJECT_API ATDCharacterDummy : public ATDCharacterBase
{
	GENERATED_BODY()

// ÇÇ°Ý
protected:
	void SetDead() override;
};
