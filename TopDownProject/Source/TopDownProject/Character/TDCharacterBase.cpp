// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"


// Sets default values
ATDCharacterBase::ATDCharacterBase()
{
 	// Pawn
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    // Movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 750.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Mesh
    GetMesh()->SetRelativeLocationAndRotation(
        FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(
        TEXT("/Script/Engine.SkeletalMesh'/Game/ElfSelena/BaseMesh/SK_ElfSelena.SK_ElfSelena'"));
    if (CharacterMeshRef.Object)
    {
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(
        TEXT("/Game/Animation/ABP_PlayerElf.ABP_PlayerElf_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }
}

void ATDCharacterBase::AttackStart()
{
    if(!bIsAttacking)
    {
        bIsAttacking = true;

        // �����߿��� �̵� �Ұ�
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

        // ���� �ӵ�
        const float AttackSpeed = 1.0f; // ���� �������� �и�

        // ��Ÿ�� ���
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        AnimInstance->Montage_Play(AttackMontage, AttackSpeed);

        // ��Ÿ�� ���� ��������Ʈ
        FOnMontageEnded EndDelegate;
        EndDelegate.BindUObject(this, &ATDCharacterBase::AttackEnd);
        AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
    }

}

void ATDCharacterBase::AttackEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
    // ��Ÿ�� ��� ���� �� ȣ��
    ensure(bIsAttacking);

    bIsAttacking = false;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ATDCharacterBase::AttackHitCheck()
{
    if (AttackProjectile)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        ATDProjectileBase* Projectile = GetWorld()->SpawnActor<ATDProjectileBase>(AttackProjectile, SpawnLocation, SpawnRotation, SpawnParams);
        if (Projectile)
        {
            Projectile->LaunchProjectile(3000.0f);
        }
    }
}
