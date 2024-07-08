// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TDProjectileBase.generated.h"

UCLASS()
class TOPDOWNPROJECT_API ATDProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDProjectileBase();

protected:
    // Collision component for detecting hits
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* CollisionComponent;

    // Projectile movement component
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // Static mesh component for visual representation
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* ProjectileMesh;

public:
    // Function to handle the projectile's movement
    void LaunchProjectile(float Speed);

};