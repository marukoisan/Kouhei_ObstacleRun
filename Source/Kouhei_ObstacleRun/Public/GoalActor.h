// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"     // í«â¡
#include "GoalActor.generated.h"

UCLASS()
class KOUHEI_OBSTACLERUN_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGoalActor();

private:


	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** GoalópÇÃStaticMesh : Goal */
	UPROPERTY(VisibleAnywhere, Category = StaticMesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** ê⁄êGîªíËópÇÃCollision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Sphere, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> Sphere;
};
