// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TDElfAttackProjectile.h"

ATDElfAttackProjectile::ATDElfAttackProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 1500.f;
	ProjectileMovementComponent->MaxSpeed = 1500.f;
}
