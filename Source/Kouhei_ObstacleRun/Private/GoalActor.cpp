// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "Character/BallPlayer.h"       //�ǉ�
#include "Kismet/KismetSystemLibrary.h" // �ǉ�"
#include "Engine/CollisionProfile.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent���쐬����
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cylinder"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);
	
	//sphereCollision��ǉ�����
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	//�R���W�����ݒ�
	//Sphere->SetCollisionProfileName(UCollisionProfile::DefaultProjectile_ProfileName);

	// Radius��ݒ肷��
	Sphere->SetSphereRadius(200.0f);

	// OnComponentBeginOverlap��Bind����
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
	
	//�傫���ύX
	SetActorRelativeScale3D(FVector(1, 1, 0.25));
}


void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ڐG����Actor��BallPlayer�����肷��
	const ABallPlayer* Player = Cast<ABallPlayer>(OtherActor);
	if (Player != nullptr)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("GOAL"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	}
}