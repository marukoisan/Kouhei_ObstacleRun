// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // �ǉ�
#include "GameFramework/SpringArmComponent.h"   // �ǉ�
#include "Camera/CameraComponent.h"             // �ǉ�
#include "InputMappingContext.h"                // �ǉ�
#include "InputActionValue.h"                   // �ǉ�
#include "BallPlayer.generated.h"

UCLASS()
class KOUHEI_OBSTACLERUN_API ABallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPlayer();

	// Scene Component
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//Character�p��Staticmesh : sphere
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Character;

	//Camera��z�u���邽�߂�SpringArm
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArm;

	//SpringArm�̐�[�ɔz�u����J����
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> Camera;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* MappingContext  ��Class���쐬����*/
	UPROPERTY(EditAnywhere, BluprintReadOnly, Category = Input, meta = (AllowPribateAccess) = "true")
		class UInputMappingContext* DefaultMappingContext;

	/* Control Input Action ��Class���쐬����*/
	UPROPERTY(EditAnywhere, BluprintReadOnly, Category = Input, meta = (AllowPrivateAccess) = "true")
		class UInputAction* ControlAction;

	/* Character��Control����*/
	void ControlCharacter(const FInputActionValue& Value);


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//���x�p�̕ϐ��Ƒ��x�̏����l
	float Speed = 300.0f;

	//�_�b�V���p�̕ϐ��Ə����l����Ȃ�������R�����g���܂�
	float Health = 100.0f;

};
