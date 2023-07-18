// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class KOUHEI_OBSTACLERUN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//�J�����̔z�u?�ƊE�p��Œ݂艺���鑕�u�̈Ӗ�(Boom)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class USpringArmComponent* CameraBoom;

	//�v���C���[�ɓ���̒����_(����������)��t�^���A
	//�����Ǐ]����(follow)�@�\����������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

};
