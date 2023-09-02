// Fill out your copyright notice in the Description page of Project Settings.


#include "CylinderActor.h"
#include "Character/BallPlayer.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ACylinderActor::ACylinderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SceneComponentを作成する
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// SceneComponentをRootComponentに設定する
	RootComponent = DefaultSceneRoot;

	// StaticMeshComponentを作成する
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cylinder"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);

	// StaticMeshComponentをRootComponentにAttachする
	StaticMesh->SetupAttachment(RootComponent);

	//物体を回転させるやつ
	StaticMesh->SetWorldRotation(FQuat(FVector(1, 0, 0), 3.14 / 2));

	//コリジョン設定
	StaticMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	
	//大きさ変更
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
	//ブロックの当たり判定を作る
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

