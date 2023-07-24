// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputTest.h"
#include "Kismet/KismetSystemLibrary.h" // ’Ç‰Á
#include "Kismet/GameplayStatics.h" // ’Ç‰Á
#include "Components/InputComponent.h" // ’Ç‰Á
#include "EnhancedInputComponent.h" // ’Ç‰Á
#include "EnhancedInputSubsystems.h" // ’Ç‰Á

// Sets default values
AEnhancedInputTest::AEnhancedInputTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//Input Action‚ğ“Ç‚İ‚İ
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Context‚ğ“Ç‚İ‚İ
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void AEnhancedInputTest::BeginPlay()
{
	Super::BeginPlay();

	//Inputİ’è‚ğs‚¤
	SetupInput();
	
}

void AEnhancedInputTest::SetupInput()
{
	//PlayerController‚ğæ“¾‚·‚é
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//“ü—Í‚ğ—LŒø‚É‚·‚é
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

		//Input Mapping Context‚ğ“o˜^‚·‚é
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

		//pressó‘Ô‚Éİ’è
		IsPressed = true;
	}
}


void AEnhancedInputTest::ReleasedAction()
{
	//Relesed
	UKismetSystemLibrary::PrintString(this, TEXT("Released"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Pressó‘Ô‚ğ‰ğœ
	IsPressed = false;
}

void AEnhancedInputTest::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();

	//Axis Input Value
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}

