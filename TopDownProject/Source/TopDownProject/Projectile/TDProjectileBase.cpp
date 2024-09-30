// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TDProjectileBase.h"


// Sets default values
ATDProjectileBase::ATDProjectileBase()
{
    // Collision Component ����
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("TDProjectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &ATDProjectileBase::OnHit);
    RootComponent = CollisionComponent;

    // Projectile Movement Component ����
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
    ProjectileMovementComponent->InitialSpeed = 500.f;
    ProjectileMovementComponent->MaxSpeed = 500.f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    // Static Mesh Component ����
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
        // ����ü�� ���� ������Ʈ�� ApplyDamageInterface�� �ִٸ� ������ ����
        if (OtherActor->GetClass()->ImplementsInterface(UTDApplyDamageInterface::StaticClass()))
        {
            ITDApplyDamageInterface* HitCharacter = Cast<ITDApplyDamageInterface>(OtherActor);
            if (HitCharacter)
            {
                // TODO: 50.0f ��ſ� applystat �Լ��� ���� ���ݷ� �����ͼ� ����������
                HitCharacter->ApplyDamage(CharacterDamage, GetInstigatorController(), this);
            }

            // ����ü�� �ı�
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
