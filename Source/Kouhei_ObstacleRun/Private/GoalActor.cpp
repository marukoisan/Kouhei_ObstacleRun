// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "Character/BallPlayer.h"       //’Ç‰Á
#include "Kismet/KismetSystemLibrary.h" // ’Ç‰Á"
#include "Engine/CollisionProfile.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent‚ğì¬‚·‚é
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMesh;

	// StaticMesh‚ğLaod‚µ‚ÄStaticMeshComponent‚ÌStaticMesh‚Éİ’è‚·‚é
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cylinder"), NULL, LOAD_None, NULL);
	StaticMesh->SetStaticMesh(Mesh);
	
	//sphereCollision‚ğ’Ç‰Á‚·‚é
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	//ƒRƒŠƒWƒ‡ƒ“İ’è
	//Sphere->SetCollisionProfileName(UCollisionProfile::DefaultProjectile_ProfileName);

	// Radius‚ğİ’è‚·‚é
	Sphere->SetSphereRadius(200.0f);

	// OnComponentBeginOverlap‚ğBind‚·‚é
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
	
	//‘å‚«‚³•ÏX
	SetActorRelativeScale3D(FVector(1, 1, 0.25));
}


void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ÚG‚µ‚½Actor‚ªBallPlayer‚©”»’è‚·‚é
	const ABallPlayer* Player = Cast<ABallPlayer>(OtherActor);
	if (Player != nullptr)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("GOAL"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	}
}