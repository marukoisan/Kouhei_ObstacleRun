// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderActor.h"
#include "Character/BallPlayer.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ACylinderActor::ACylinderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SceneComponent���쐬����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// SceneComponent��RootComponent�ɐݒ肷��
	RootComponent = DefaultSceneRoot;

	// StaticMeshComponent���쐬����
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cylinder"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);

	// StaticMeshComponent��RootComponent��Attach����
	StaticMesh->SetupAttachment(RootComponent);

	//���̂���]��������
	StaticMesh->SetWorldRotation(FQuat(FVector(1, 0, 0), 3.14 / 2));

	//�R���W�����ݒ�
	StaticMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	
	//�傫���ύX
	SetActorRelativeScale3D(FVector(1, 1, 12));
}

// Called when the game starts or when spawned
void ACylinderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACylinderActor::Tick(float DeltaTime)
{
	//�u���b�N�̓����蔻������
	FVector move = {0, 0, 0};
	FHitResult  Hit;
	
	Super::Tick(DeltaTime);
	StaticMesh->AddWorldRotation(FQuat(FVector(0, 0, 1), 3.14 / 200),true,&Hit);
	//AddActorWorldOffset(FVector(move * DeltaTime), true, &Hit);

	ABallPlayer* player = Cast<ABallPlayer>(Hit.GetActor());
	if (player != nullptr)
	{
		player->AddActorWorldOffset(Hit.Normal * -1);
	}

	
}

