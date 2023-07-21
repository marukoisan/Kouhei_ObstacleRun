// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	//Input Mapping Context「IM_Controls」を読み込む
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	//Input Action「IA_Control」を読み込む
	ControlAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context・・・ ConstructorのComponent設定処理
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//ControlCharacterとIA_ControlのTRiggeredをBindする
		EnhancedInputComponent->BindAction(ControlAction, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);
	}

}

void ABallPlayer::ControlCharacter(const FInputActionValue& Value)
{
	//inputのValueはVector2Dに変換できる
	FVector2D v = Value.Get<FVector2D>();

	//Vectorを計算する
	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	// Characterに力を加える
	Character->AddForce(ForceVector, NAME_None, true);
}