// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputTest.h"
#include "Kismet/KismetSystemLibrary.h" // 追加
#include "Kismet/GameplayStatics.h" // 追加
#include "Components/InputComponent.h" // 追加
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加

// Sets default values
AEnhancedInputTest::AEnhancedInputTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//Input Actionを読み込み
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Contextを読み込み
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void AEnhancedInputTest::BeginPlay()
{
	Super::BeginPlay();

	//Input設定を行う
	SetupInput();
	
}

void AEnhancedInputTest::SetupInput()
{
	//PlayerControllerを取得する
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//入力を有効にする
	EnableInput(controller);

	if (InputComponent)
	{
		//Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			//Input Action
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Triggered, this, &AEnhancedInputTest::PressedAction);
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Completed, this, &AEnhancedInputTest::ReleasedAction);

			//input Axis
			EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &AEnhancedInputTest::PressedAxis);
			
		}

		//Input Mapping Contextを登録する
		if (APlayerController* PlayerController = Cast<APlayerController>(controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}	
	}
}

void AEnhancedInputTest::PressedAction()
{
	if (!IsPressed)
	{
		//pressed
		UKismetSystemLibrary::PrintString(this, TEXT("Pressed"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

		//press状態に設定
		IsPressed = true;
	}
}


void AEnhancedInputTest::ReleasedAction()
{
	//Relesed
	UKismetSystemLibrary::PrintString(this, TEXT("Released"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Press状態を解除
	IsPressed = false;
}

void AEnhancedInputTest::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();

	//Axis Input Value
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}

