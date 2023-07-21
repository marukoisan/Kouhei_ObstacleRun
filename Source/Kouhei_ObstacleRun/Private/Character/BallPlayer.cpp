// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	//Input Mapping Context�uIM_Controls�v��ǂݍ���
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	//Input Action�uIA_Control�v��ǂݍ���
	ControlAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context�E�E�E Constructor��Component�ݒ菈��
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//ControlCharacter��IA_Control��TRiggered��Bind����
		EnhancedInputComponent->BindAction(ControlAction, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);
	}

}

void ABallPlayer::ControlCharacter(const FInputActionValue& Value)
{
	//input��Value��Vector2D�ɕϊ��ł���
	FVector2D v = Value.Get<FVector2D>();

	//Vector���v�Z����
	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	// Character�ɗ͂�������
	Character->AddForce(ForceVector, NAME_None, true);
}