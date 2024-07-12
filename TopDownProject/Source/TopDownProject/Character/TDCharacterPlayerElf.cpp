// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TDCharacterPlayerElf.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATDCharacterPlayerElf::ATDCharacterPlayerElf()
{
	// ī�޶�
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->SetRelativeRotation(FRotator(-50.0f, 180.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;

	// ���� ��ǥ�� ȸ�� ��� ����
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// ��ǲ
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	if (InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Attack.IA_Attack'"));
	if (InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}

}

void ATDCharacterPlayerElf::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerContorller = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerContorller->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATDCharacterPlayerElf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �ݵ�� EnhancedInput�� ����ϵ��� CastCheck
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDCharacterPlayerElf::Move);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATDCharacterPlayerElf::Attack);
}

void ATDCharacterPlayerElf::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ATDCharacterPlayerElf::Attack(const FInputActionValue& Value)
{
	AttackStart();
}

