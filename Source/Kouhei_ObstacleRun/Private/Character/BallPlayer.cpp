// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player (���̃|�[�����ŏ��l�̃v���C���[�Ő��䂳���悤�ɐݒ�)
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Sphere;

	//StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Sphere"), NULL, LOAD_None, NULL);

	//StaticMesh��StaticMeshComponent�ɐݒ肷��
	Sphere->SetStaticMesh(Mesh);

	//Material��StaticMesh�ɐݒ肷��
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Engine/BasicShapes/BasicShapeMaterial"), NULL, LOAD_None, NULL);

	//Material��StaticMeshComponent�ɐݒ肷��
	Sphere->SetMaterial(0, Material);

	//Simulate Physics��L���ɂ���
	Sphere->SetSimulatePhysics(true);

	//SpringArm��ǉ�����
	//RootComponent���p�x��ς���
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//�p�x��ύX���� Frotator(Pitch(Y), Yaw(Z), Roll(X))
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	//Spring Arm�̒����𒲐�����
	//�v���C���[�ƃJ�����̋���
	SpringArm->TargetArmLength = 450.0f;

	//SpringArm����̊p�x���p�����Ȃ�
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	//Camera��Lag��L���ɂ���
	SpringArm->bEnableCameraLag = true;

	//Camera��ǉ�����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
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

