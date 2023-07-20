// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"

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

	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

