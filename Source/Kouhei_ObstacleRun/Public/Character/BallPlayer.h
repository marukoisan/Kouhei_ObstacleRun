// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // �ǉ�
#include "GameFramework/SpringArmComponent.h"   // �ǉ�
#include "Camera/CameraComponent.h"             // �ǉ�
#include "Components/ArrowComponent.h"			// �ǉ�
#include "InputMappingContext.h"                // �ǉ�
#include "InputAction.h"                        // �ǉ�
#include "InputActionValue.h"                   // �ǉ�
#include "EnhancedInputComponent.h"             // �ǉ�
#include "EnhancedInputSubsystems.h"            // �ǉ�
#include "Components/CapsuleComponent.h"        // �ǉ�
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

	//CapsuleComponent�̍쐬
	UPROPERTY(Category = CapsuleComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCapsuleComponent> CapsuleComponent;


	// Called to bind functionality to input
	//Called to vind functionlity to input(�@�\���Ăяo���Ă��܂�)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		//Set up action bindings(�ڑ�����)
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//ControlBall��IA_Control��Triggered��Bind����
			EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);

			//Look��IA_Look��Triggered��Bind����
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABallPlayer::Look);
		}

	}


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
	//�i�s������\������ArrowComponent
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UArrowComponent> Arrow;//Arrow�ϐ����쐬

	/*********/

	/* Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPriateAccess = "true"))
		class UInputAction* LookAction;//�ϐ��ł�

	/* �n�_�𑀍삷�邽�߂̊֐� */
	void Look(const FInputActionValue& Value);

	/* �W�����v���� */
	void Jump(const FInputActionValue& Value);

	/*  Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPribateAccess = "true"))
		class UInputAction* JumpAction;

	/*Hit Event��Binding����֐�*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	//���x�p�̕ϐ��Ƒ��x�̏����l
	float Speed = 10.0f;

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

	//�W�����v�ɉ������
	float JumpImpluse = 200.0f;

	//�W�����v���ł��邩���肷��t���O
	bool CanJump = false;
};

