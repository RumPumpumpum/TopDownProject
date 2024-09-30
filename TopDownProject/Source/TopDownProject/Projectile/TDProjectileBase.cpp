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
}

void ATDProjectileBase::LaunchProjectile()
{
    ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);
	ProjectileMovementComponent->Activate();
}

void ATDProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this)
    {
        // 투사체에 맞은 오브젝트에 ApplyDamageInterface가 있다면 데미지 적용
        if (OtherActor->GetClass()->ImplementsInterface(UTDApplyDamageInterface::StaticClass()))
        {
            ITDApplyDamageInterface* HitCharacter = Cast<ITDApplyDamageInterface>(OtherActor);
            if (HitCharacter)
            {
                // TODO: 50.0f 대신에 applystat 함수를 통해 공격력 가져와서 데미지적용
                HitCharacter->ApplyDamage(CharacterDamage, GetInstigatorController(), this);
            }

            // 투사체를 파괴
            Destroy();
        }
    }
}

void ATDProjectileBase::ApplyStat(float NewCharacterDamage, float NewProjectileSpeed, float NewProjectileRange)
{
    CharacterDamage = NewCharacterDamage;
    ProjectileSpeed = NewProjectileSpeed;
    ProjectileRange = NewProjectileRange;

    SetLifeSpan(NewProjectileRange);
}
