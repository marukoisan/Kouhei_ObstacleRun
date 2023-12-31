// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "Character/BallPlayer.h"       //追加
#include "Kismet/KismetSystemLibrary.h" // 追加"
#include "Engine/CollisionProfile.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponentを作成する
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cylinder"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);
	
	//sphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	//コリジョン設定
	//Sphere->SetCollisionProfileName(UCollisionProfile::DefaultProjectile_ProfileName);

	// Radiusを設定する
	Sphere->SetSphereRadius(200.0f);

	// OnComponentBeginOverlapをBindする
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
	
	//大きさ変更
	SetActorRelativeScale3D(FVector(1, 1, 0.25));
}


void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 接触したActorがBallPlayerか判定する
	const ABallPlayer* Player = Cast<ABallPlayer>(OtherActor);
	if (Player != nullptr)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("GOAL"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	}
}