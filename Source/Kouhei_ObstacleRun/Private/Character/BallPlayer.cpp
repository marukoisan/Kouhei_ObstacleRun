// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "Kismet/KismetSystemLibrary.h" // �ǉ�
#include "Kismet/GameplayStatics.h"     // �ǉ�
#include "Components/InputComponent.h"  // �ǉ�
#include "EnhancedInputComponent.h"     // �ǉ�
#include "EnhancedInputSubsystems.h"    // �ǉ�
#include "Kismet/GamePlayStatics.h"     // �ǉ�
#include "Kismet/KismetMathLibrary.h"	// �ǉ�

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player (���̃|�[�����ŏ��l�̃v���C���[�Ő��䂳���悤�ɐݒ�)
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//SceneComponent���쐬����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponent��RootComponent�ɐݒ肷��
	//RootComponent = DefaultSceneRoot;

	//CapsuleComponent�̐ݒ�
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//�u���[�v�����g����\���Ŕ����ł��܂�
	CapsuleComponent->SetMobility(EComponentMobility::Movable);
	CapsuleComponent->SetCapsuleHalfHeight(90.0, true);
	CapsuleComponent->SetCapsuleRadius(35.0, true);
	CapsuleComponent->SetEnableGravity(true);
	CapsuleComponent->SetLinearDamping(0.01);
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	//�v���C���[�̃R���W�����ݒ�̂Ƃ���
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	//Overlap�̃C�x���g�𔭐�������
	CapsuleComponent->SetGenerateOverlapEvents(true);
	//�����������v���V�L�Ƀ��v���P�[�g�����ꍇ��true
	CapsuleComponent->bReplicatePhysicsToAutonomousProxy;
	//PhysicsVolume���X�V���邩�ǂ����𔻒f���܂��B
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	
	//RootComponent��CapsuleComponent������
	RootComponent = CapsuleComponent;
	
	/******************/

	//StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	Character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("USkeletalMeshComponent"));

	//StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	Character->SetSkeletalMesh(Mesh);

	//Character��RootComponentni��Attach����
	Character->SetupAttachment(CapsuleComponent);

	//Material��StaticMesh�ɐݒ肷��
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Characters/Mannequins/Materials/Instances/Quinn/MI_Quinn_01"), NULL, LOAD_None, NULL);

	//Material��StaticMeshComponent�ɐݒ肷��
	Character->SetMaterial(0, Material);

	//Simulate Physics��L���ɂ���
	//Character->SetSimulatePhysics(true);
	//CollisionBodyInstances


	//Character��Rotation�̐ݒ������
	Character->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Character->SetRelativeLocation(FVector(0.0f, 0.0f, -93.0f));
	

	//CapsuleComponent��e�q�t��
	//CapsuleComponent->SetupAttachment(DefaultSceneRoot);
	
	/*************/

	//SpringArm��ǉ�����
	//RootComponent���p�x��ς���
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//Pawn��ControllerRotation���g�p���邽�ߎg�p���Ȃ�(�R���g���[���[�̊p�x���D�悳��邩��)
	//Spring Arm�̒����𒲐�����
	//�p�x��ύX���� Frotator(Pitch(Y), Yaw(Z), Roll(X))
	//SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	//�v���C���[�ƃJ�����̋���
	SpringArm->TargetArmLength = 150.0f;

	//Pawn��ControllerRotation���g�p����
	SpringArm->bUsePawnControlRotation = true;

	//Pawn��ControllerRotation���g�p���邽�ߎg�p���Ȃ�
	//SpringArm����̊p�x���p�����Ȃ�
	/*SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;*/

	//Camera��Lag��L���ɂ���
	SpringArm->bEnableCameraLag = true;

	//Camera��ǉ�����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	//Camera�̈ʒu��ύX����
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f,  140.0f));

	// MotionBlur���I�t�ɂ���
	//�J������Motion Blur�𖳌��ɂ��邱�ƂŃv���C���[�̓������N���ɂȂ�܂��B
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	//Set Field Of View
	Camera->SetFieldOfView(90.0f);

	/*************/
	//Arrow��ǉ�����
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(Camera);

	//Character�̓���Ɉړ�����悤��Location��ݒ肷��
	Arrow->SetRelativeLocation(FVector(400.0f, 0.0f, 200.0f));

	// Arrow��\��������悤�ɂ���
	//��Ō����Ȃ��Ȃ�悤�ɂ���̂�true�ɂ���̂�Y��Ȃ��悤�ɂ���
	Arrow->bHiddenInGame = false;

	/*************/

	//Input Action��ǂݍ���
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Context��ǂݍ���
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	// Input Action�́uIA_Look�v��ǂݍ���
	LookAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Look"), NULL, LOAD_None, NULL);
	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Input�ݒ���s��
	SetupInput();
	
	////Add Input Mapping Context
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//	}
	//}

}


void ABallPlayer::SetupInput()
{
	//PlayerController���擾����
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//���͂�L���ɂ���
	EnableInput(controller);

	if (InputComponent)
	{
		//Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			//Input Action
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Triggered, this, &ABallPlayer::PressedAction);
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Completed, this, &ABallPlayer::ReleasedAction);

			//input Axis
			EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::PressedAxis);

		}

		//Input Mapping Context��o�^����
		if (APlayerController* PlayerController = Cast<APlayerController>(controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	////mappingcontext��ݒ肷��
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//	}
	//}
}

//�R���g���[���̊p�x��ύX���āA�J�����̑���𐧌䂷�鏈�����������܂�
void ABallPlayer::Look(const FInputActionValue& Value)
{
	//input��Value��Vector2D�ɕϊ��ł���
	FVector2D v = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//�R���g���[���Ƀ��[���͂ƃs�b�`���͂�ǉ�����
		AddControllerYawInput(v.X);
		AddControllerPitchInput(v.Y);

		//Pawn�������Ă���Control�̊p�x���擾����
		FRotator controlRotate = GetControlRotation();

		//controller��Pitch�̊p�x�𐧌�����
		double limitPitchAngle = UKismetMathLibrary::ClampAngle(controlRotate.Pitch, -40.0f, -10.0f);

		//PlayerController�̊p�x��ݒ肷��
		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(controlRotate.Pitch, controlRotate.Yaw, 0.0f));
	}
}



void ABallPlayer::PressedAction()
{
	if (!IsPressed)
	{
		//pressed
		UKismetSystemLibrary::PrintString(this, TEXT("Pressed"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

		//press��Ԃɐݒ�
		IsPressed = true;
	}
}


void ABallPlayer::ReleasedAction()
{
	//Relesed
	UKismetSystemLibrary::PrintString(this, TEXT("Released"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Press��Ԃ�����
	IsPressed = false;
}

//void ABallPlayer::SetupInput(UInputComponent* PlayerInputComponent)
//{
//	
//	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
//	{
//		EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);
//	}
//
//}


void ABallPlayer::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();
	
	
	//find out which way is forward�����𓾂����
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//get foward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//get right vector
	const FVector FightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//���[���h�ɒu����Ă�����W�����Ă��邩(�A�N�^�[)
	this->AddActorLocalOffset(ForwardDirection * v.Y * Speed, true);
	AddActorLocalOffset(FightDirection * v.X * Speed, true);

	
	//�X�^�e�b�N���b�V���̍��W�����Ă���(�r���[�|�[�g���)
	//�R���|�[�l���g�̒��ɂ�����W
	//Character->AddWorldOffset(ForwardDirection,v.Y);
	//Character->AddWorldOffset(FightDirection,v.X);
	
	////Vector���v�Z����
	//FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	//// Character�ɗ͂�������
	//Character->AddForce(ForceVector, NAME_None, true);

	//Axis Input Value
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}

void ABallPlayer::ControlCharacter(const FInputActionValue& Value)
{
	//input��Value��Vector2D�ɕϊ��ł���
	FVector2D v = Value.Get<FVector2D>();

	//Vector���v�Z����
	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	//Arrow�̐i�s������Vector���v�Z����
	FVector ArrowForceVector = UKismetMathLibrary::TransformDirection(Arrow->GetComponentToWorld(), ForceVector);

	//Character�ɗ͂�������
	Character->AddForce(ForceVector, NAME_Name, true);

}