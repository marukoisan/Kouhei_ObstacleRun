// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // �ǉ�
#include "GameFramework/SpringArmComponent.h"   // �ǉ�
#include "Camera/CameraComponent.h"             // �ǉ�
#include "InputMappingContext.h"                // �ǉ�
#include "InputAction.h"                        // �ǉ�
#include "InputActionValue.h"                   // �ǉ�
#include "EnhancedInputComponent.h"             // �ǉ�
#include "EnhancedInputSubsystems.h"            // �ǉ�
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/************/

		/** Called for Action input */
	void EventAction(const FInputActionValue& Value);

	/** Called for Axis input */
	void EventAxis(const FInputActionValue& Value);


	/* MappingContext */
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputMappingContext* DefaultMappingContext;

	/* Action Input */
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* ActionInput;

	/* Axis Input */
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* AxisInput;

	/***********/

	/* Character�̃R���g���[�� */
	void ControlCharacter(const FInputActionValue& Value);

	/**********/

	/* Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPriateAccess = "true"))
		class UInputAction* LookAction;//�ϐ��ł�

	/* �n�_�𑀍삷�邽�߂̊֐� */
	void Look(const FInputActionValue& Value);

private:
	//���x�p�̕ϐ��Ƒ��x�̏����l
	float Speed = 300.0f;

	//�_�b�V���p�̕ϐ��Ə����l����Ȃ�������R�����g���܂�
	float Health = 100.0f;

	//Input�ݒ�
	void SetupInput();

	//Input Event(Action) �C�x���g�n���h�G���[�֐�
	void PressedAction();
	void ReleasedAction();

	//Input Event(Axis) �C�x���g�n���h�G���[�֐�
	void PressedAxis(const FInputActionValue& Value);


	// Press��Ԃ��Ǘ�
	bool IsPressed = false;
};

