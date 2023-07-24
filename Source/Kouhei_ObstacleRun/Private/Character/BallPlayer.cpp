// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "Kismet/KismetSystemLibrary.h" // �ǉ�
#include "Kismet/GameplayStatics.h" // �ǉ�
#include "Components/InputComponent.h" // �ǉ�
#include "EnhancedInputComponent.h" // �ǉ�
#include "EnhancedInputSubsystems.h" // �ǉ�

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
	RootComponent = DefaultSceneRoot;

	//StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	Character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("USkeletalMeshComponent"));
	//RootComponent = Character;

	//StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	Character->SetSkeletalMesh(Mesh);

	//Character��RootComponentni��Attach����
	Character->SetupAttachment(RootComponent);

	//Material��StaticMesh�ɐݒ肷��
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Characters/Mannequins/Materials/Instances/Quinn/MI_Quinn_01"), NULL, LOAD_None, NULL);

	//Material��StaticMeshComponent�ɐݒ肷��
	Character->SetMaterial(0, Material);

	//Simulate Physics��L���ɂ���
	Character->SetSimulatePhysics(true);

	//Character��Rotation�̐ݒ������
	Character->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	/*************/

	//SpringArm��ǉ�����
	//RootComponent���p�x��ς���
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//Spring Arm�̒����𒲐�����
	//�p�x��ύX���� Frotator(Pitch(Y), Yaw(Z), Roll(X))
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	//�v���C���[�ƃJ�����̋���
	SpringArm->TargetArmLength = 150.0f;

	//SpringArm����̊p�x���p�����Ȃ�
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	//Camera��Lag��L���ɂ���
	SpringArm->bEnableCameraLag = true;

	//Camera��ǉ�����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	//Camera�̈ʒu��ύX����
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f,  45.0f));

	// MotionBlur���I�t�ɂ���
	//�J������Motion Blur�𖳌��ɂ��邱�ƂŃv���C���[�̓������N���ɂȂ�܂��B
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	/*************/

	//Input Action��ǂݍ���
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Context��ǂݍ���
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Input�ݒ���s��
	SetupInput();
	
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

void ABallPlayer::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();

	//Axis Input Value
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}



//void ABallPlayer::PressedAxis(const FInputActionValue& Value)
//{
//	//input��Value��Vector2D�ɕϊ��ł���
//	FVector2D v = Value.Get<FVector2D>();
//
//	//Vector���v�Z����
//	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;
//
//	// Character�ɗ͂�������
//	Character->AddForce(ForceVector, NAME_None, true);
//}