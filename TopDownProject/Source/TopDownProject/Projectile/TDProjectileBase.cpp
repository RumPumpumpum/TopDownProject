// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TDProjectileBase.h"


// Sets default values
ATDProjectileBase::ATDProjectileBase()
{
    // Collision Component 생성
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("TDProjectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &ATDProjectileBase::OnHit);
    RootComponent = CollisionComponent;

    // Projectile Movement Component 생성
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
    ProjectileMovementComponent->InitialSpeed = 500.f;
    ProjectileMovementComponent->MaxSpeed = 500.f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    // Static Mesh Component 생성
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(RootComponent);

    // 공격 사거리, 추후 AttackRange 영향받도록 설정
    InitialLifeSpan = 3.0f;
}

void ATDProjectileBase::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

void ATDProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this)
    {
        if (OtherActor->GetClass()->ImplementsInterface(UTDApplyDamageInterface::StaticClass()))
        {
            ITDApplyDamageInterface* HitCharacter = Cast<ITDApplyDamageInterface>(OtherActor);
            if (HitCharacter)
            {
                HitCharacter->ApplyDamage(50.0f, GetInstigatorController(), this);
            }

            // 투사체를 파괴
            Destroy();
        }
    }
}
