// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // 追加
#include "GameFramework/SpringArmComponent.h"   // 追加
#include "Camera/CameraComponent.h"             // 追加
#include "InputMappingContext.h"                // 追加
#include "InputActionValue.h"                   // 追加
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* MappingContext  のClassを作成する*/
	UPROPERTY(EditAnywhere, BluprintReadOnly, Category = Input, meta = (AllowPribateAccess) = "true")
		class UInputMappingContext* DefaultMappingContext;

	/* Control Input Action のClassを作成する*/
	UPROPERTY(EditAnywhere, BluprintReadOnly, Category = Input, meta = (AllowPrivateAccess) = "true")
		class UInputAction* ControlAction;

	/* CharacterをControlする*/
	void ControlCharacter(const FInputActionValue& Value);


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//速度用の変数と速度の初期値
	float Speed = 300.0f;

	//ダッシュ用の変数と初期値いらなかったらコメントします
	float Health = 100.0f;

};
