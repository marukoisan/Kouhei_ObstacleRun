// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "Kismet/KismetSystemLibrary.h" // 追加
#include "Kismet/GameplayStatics.h" // 追加
#include "Components/InputComponent.h" // 追加
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player (このポーンが最小値のプレイヤーで制御されるように設定)
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//SceneComponentを作成する
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	//SceneComponentをRootComponentに設定する
	RootComponent = DefaultSceneRoot;

	//StaticMeshComponentを追加し、RootComponentに設定する
	Character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("USkeletalMeshComponent"));
	//RootComponent = Character;

	//StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	Character->SetSkeletalMesh(Mesh);

	//CharacterをRootComponentniにAttachする
	Character->SetupAttachment(RootComponent);

	//MaterialをStaticMeshに設定する
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Characters/Mannequins/Materials/Instances/Quinn/MI_Quinn_01"), NULL, LOAD_None, NULL);

	//MaterialをStaticMeshComponentに設定する
	Character->SetMaterial(0, Material);

	//Simulate Physicsを有効にする
	Character->SetSimulatePhysics(true);

	//CharacterのRotationの設定をする
	Character->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	/*************/

	//SpringArmを追加する
	//RootComponent→角度を変える
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//Spring Armの長さを調整する
	//角度を変更する Frotator(Pitch(Y), Yaw(Z), Roll(X))
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	//プレイヤーとカメラの距離
	SpringArm->TargetArmLength = 150.0f;

	//SpringArmからの角度を継承しない
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	//CameraのLagを有効にする
	SpringArm->bEnableCameraLag = true;

	//Cameraを追加する
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	//Cameraの位置を変更する
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f,  45.0f));

	// MotionBlurをオフにする
	//カメラのMotion Blurを無効にすることでプレイヤーの動きが鮮明になります。
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	/*************/

	//Input Actionを読み込み
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Contextを読み込み
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Input設定を行う
	SetupInput();
	
}


void ABallPlayer::SetupInput()
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
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Triggered, this, &ABallPlayer::PressedAction);
			EnhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Completed, this, &ABallPlayer::ReleasedAction);

			//input Axis
			EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::PressedAxis);

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


void ABallPlayer::PressedAction()
{
	if (!IsPressed)
	{
		//pressed
		UKismetSystemLibrary::PrintString(this, TEXT("Pressed"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

		//press状態に設定
		IsPressed = true;
	}
}


void ABallPlayer::ReleasedAction()
{
	//Relesed
	UKismetSystemLibrary::PrintString(this, TEXT("Released"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Press状態を解除
	IsPressed = false;
}

void ABallPlayer::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();

	//Axis Input Value
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}



//void ABallPlayer::PressedAxis(const FInputActionValue& Value)
//{
//	//inputのValueはVector2Dに変換できる
//	FVector2D v = Value.Get<FVector2D>();
//
//	//Vectorを計算する
//	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;
//
//	// Characterに力を加える
//	Character->AddForce(ForceVector, NAME_None, true);
//}