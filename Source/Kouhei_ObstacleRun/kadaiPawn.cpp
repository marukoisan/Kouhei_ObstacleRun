// Fill out your copyright notice in the Description page of Project Settings.


#include "kadaiPawn.h"

// Sets default values
AkadaiPawn::AkadaiPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by set the lowest-numbered player (���̃|�[�����ŏ��n�̃v���C���[�Ő��䂳���悤�ɐݒ�)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//create adummy root component we can attach things to.(�e�q�t���\�ȃ_�~�[�̃��[�g�R���|�[�l���g���쐬)
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));

}

// Called when the game starts or when spawned
void AkadaiPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AkadaiPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AkadaiPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

