// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // 追加
#include "GameFramework/SpringArmComponent.h"   // 追加
#include "Camera/CameraComponent.h"             // 追加
#include "Components/ArrowComponent.h"			// 追加
#include "InputMappingContext.h"                // 追加
#include "InputAction.h"                        // 追加
#include "InputActionValue.h"                   // 追加
#include "EnhancedInputComponent.h"             // 追加
#include "EnhancedInputSubsystems.h"            // 追加
#include "Components/CapsuleComponent.h"        // 追加
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

	//Character用のStaticmesh : sphere
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Character;

	//Cameraを配置するためのSpringArm
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArm;

	//SpringArmの先端に配置するカメラ
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> Camera;

	//CapsuleComponentの作成
	UPROPERTY(Category = CapsuleComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCapsuleComponent> CapsuleComponent;


	// Called to bind functionality to input
	//Called to vind functionlity to input(機能を呼び出しています)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		//Set up action bindings(接続する)
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//ControlBallとIA_ControlのTriggeredをBindする
			EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);

			//LookとIA_LookのTriggeredをBindする
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

	/* Characterのコントロール */
	void ControlCharacter(const FInputActionValue& Value);

	/**********/
	//進行方向を表示するArrowComponent
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UArrowComponent> Arrow;//Arrow変数を作成

	/*********/

	/* Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPriateAccess = "true"))
		class UInputAction* LookAction;//変数です

	/* 始点を操作するための関数 */
	void Look(const FInputActionValue& Value);

	/* ジャンプする */
	void Jump(const FInputActionValue& Value);

	/*  Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPribateAccess = "true"))
		class UInputAction* JumpAction;

	/*Hit EventをBindingする関数*/
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	//速度用の変数と速度の初期値
	float Speed = 10.0f;

	//ダッシュ用の変数と初期値いらなかったらコメントします
	float Health = 100.0f;

	//Input設定
	void SetupInput();

	//Input Event(Action) イベントハンドエラー関数
	void PressedAction();
	void ReleasedAction();

	//Input Event(Axis) イベントハンドエラー関数
	void PressedAxis(const FInputActionValue& Value);


	// Press状態を管理
	bool IsPressed = false;

	//ジャンプに加える力
	float JumpImpluse = 200.0f;

	//ジャンプができるか判定するフラグ
	bool CanJump = false;
};

