// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"     // �ǉ�
#include "GameFramework/SpringArmComponent.h"   // �ǉ�
#include "Camera/CameraComponent.h"             // �ǉ�
#include "BallPlayer.generated.h"

UCLASS()
class KOUHEI_OBSTACLERUN_API ABallPlayer : public APawn
{
	GENERATED_BODY()

//protected:
	//character�p��Staticmesh : sphere
	//UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<UStaticMeshComponent> Character;

	////Camera��z�u���邽�߂�SpringArm
	//UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<USpringArmComponent> SpringArm;

	////SpringArm�̐�[�ɔz�u����J����
	//UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<UCameraComponent> Camera;
public:
	// Sets default values for this pawn's properties
	ABallPlayer();

	// Scene Component
	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	//character�p��Staticmesh : sphere
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
