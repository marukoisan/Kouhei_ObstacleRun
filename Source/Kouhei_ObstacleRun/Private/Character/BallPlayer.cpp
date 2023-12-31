// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BallPlayer.h"
#include "Kismet/KismetSystemLibrary.h" // 追加
#include "Kismet/GameplayStatics.h"     // 追加
#include "Components/InputComponent.h"  // 追加
#include "EnhancedInputComponent.h"     // 追加
#include "EnhancedInputSubsystems.h"    // 追加
#include "Kismet/GamePlayStatics.h"     // 追加
#include "Kismet/KismetMathLibrary.h"	// 追加
#include "Engine/CollisionProfile.h"    // 追加

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
	//RootComponent = DefaultSceneRoot;

	//CapsuleComponentの設定
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//ブループリントから予測で発見できます
	CapsuleComponent->SetMobility(EComponentMobility::Movable);
	CapsuleComponent->SetCapsuleHalfHeight(90.0, true);
	CapsuleComponent->SetCapsuleRadius(35.0, true);
	CapsuleComponent->SetEnableGravity(true);
	CapsuleComponent->SetLinearDamping(0.01);
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	//プレイヤーのコリジョン設定のところ
	//CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);


	//Overlapのイベントを発生させる
	CapsuleComponent->SetGenerateOverlapEvents(true);
	//物理が自動プロシキにレプリケートされる場合はtrue
	//CapsuleComponent->bReplicatePhysicsToAutonomousProxy;
	//PhysicsVolumeを更新するかどうかを判断します。
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);

	//Hit Eventを有効にする
	CapsuleComponent->BodyInstance.bNotifyRigidBodyCollision = true;

	

	//物理演算の設定をオンにする
	//CapsuleComponent->SetSimulatePhysics(true);

	//重力の設定をオンにする
	CapsuleComponent->SetEnableGravity(true);
	
	//RootComponentにCapsuleComponentを入れる
	RootComponent = CapsuleComponent;
	
	/******************/

	//StaticMeshComponentを追加し、RootComponentに設定する
	Character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("USkeletalMeshComponent"));

	//StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple"), NULL, LOAD_None, NULL);

	//StaticMeshをStaticMeshComponentに設定する
	Character->SetSkeletalMesh(Mesh);

	//CharacterをRootComponentniにAttachする
	Character->SetupAttachment(CapsuleComponent);

	//MaterialをStaticMeshに設定する
	UMaterial* Material = LoadObject<UMaterial>(NULL, TEXT("/Game/Characters/Mannequins/Materials/Instances/Quinn/MI_Quinn_01"), NULL, LOAD_None, NULL);

	//MaterialをStaticMeshComponentに設定する
	Character->SetMaterial(0, Material);

	//Simulate Physicsを有効にする
	//Character->SetSimulatePhysics(true);
	//CollisionBodyInstances

	//CollisionPrisetを「PhysicsActor」に変更する

	//Character->SetCollisionProfileName(TEXT("PhysicsActor"));

	//Hit Eventを有効にする
	//Character->BodyInstance.bNotifyRigidBodyCollision = true;

	//CharacterのRotationの設定をする
	Character->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Character->SetRelativeLocation(FVector(0.0f, 0.0f, -93.0f));
	
	//重力の設定をしてみる
	//Character->SetEnableBodyGravity(true,);


	//CapsuleComponentを親子付け
	//CapsuleComponent->SetupAttachment(DefaultSceneRoot);

	//set Animation Mode
	Character->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimObj(TEXT("AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Manny'"));
	Character->SetAnimClass(AnimObj.Object->GeneratedClass);

	
	/*************/

	//SpringArmを追加する
	//RootComponent→角度を変える
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	//PawnのControllerRotationを使用するため使用しない(コントローラーの角度が優先されるから)
	//Spring Armの長さを調整する
	//角度を変更する Frotator(Pitch(Y), Yaw(Z), Roll(X))
	//SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	//プレイヤーとカメラの距離
	SpringArm->TargetArmLength = 150.0f;

	//PawnのControllerRotationを使用する
	SpringArm->bUsePawnControlRotation = true;

	//PawnのControllerRotationを使用するため使用しない
	//SpringArmからの角度を継承しない
	/*SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;*/

	//CameraのLagを有効にする
	SpringArm->bEnableCameraLag = true;

	//Cameraを追加する
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	//Cameraの位置を変更する
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f,  140.0f));

	// MotionBlurをオフにする
	//カメラのMotion Blurを無効にすることでプレイヤーの動きが鮮明になります。
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	//Set Field Of View
	Camera->SetFieldOfView(90.0f);

	/*************/
	//Arrowを追加する
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(Camera);

	//Characterの頭上に移動するようにLocationを設定する
	Arrow->SetRelativeLocation(FVector(400.0f, 0.0f, 200.0f));

	// Arrowを表示させるようにする
	//後で見えなくなるようにするのでtrueにするのを忘れないようにする
	Arrow->bHiddenInGame = true;

	/*************/

	//Input Actionを読み込み
	ActionInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);
	AxisInput = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Control"), NULL, LOAD_None, NULL);

	//Input Mapping Contextを読み込み
	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Mapping/IM_Controls"), NULL, LOAD_None, NULL);

	// Input Actionの「IA_Look」を読み込む
	LookAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Look"), NULL, LOAD_None, NULL);

	//Input Actionの「IA_Jump」を読み込む
	JumpAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Mapping/IA_Jump"), NULL, LOAD_None, NULL);

	//アニメーションBPを読み込む
	//Animation = LoadObject<>
	
	
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Input設定を行う
	SetupInput();
	
	////Add Input Mapping Context
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//	}
	//}

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
			//Input ActionをIA_Jumpに置き換える
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABallPlayer::PressedAction);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABallPlayer::ReleasedAction);

			//JumpとIA_JumpのTriggerdをBindする
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABallPlayer::Jump);

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

	////mappingcontextを設定する
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//	}
	//}
}

//コントローラの角度を変更して、カメラの操作を制御する処理を実装します
void ABallPlayer::Look(const FInputActionValue& Value)
{
	//inputのValueはVector2Dに変換できる
	FVector2D v = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//コントローラにヨー入力とピッチ入力を追加する
		AddControllerYawInput(v.X);
		AddControllerPitchInput(v.Y);

		//Pawnが持っているControlの角度を取得する
		FRotator controlRotate = GetControlRotation();

		//controllerのPitchの角度を制限する
		double limitPitchAngle = UKismetMathLibrary::ClampAngle(controlRotate.Pitch, -40.0f, -10.0f);

		//PlayerControllerの角度を設定する
		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(controlRotate.Pitch, controlRotate.Yaw, 0.0f));
	}
}



void ABallPlayer::PressedAction()
{
	if (!IsPressed)
	{
		void Jump(const FInputActionValue & Value);
		//pressed
		//UKismetSystemLibrary::PrintString(this, TEXT("Pressed"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

		//press状態に設定
		IsPressed = true;
	}
}


void ABallPlayer::ReleasedAction()
{
	//Relesed
	//UKismetSystemLibrary::PrintString(this, TEXT("Released"), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Press状態を解除
	IsPressed = false;
}

//void ABallPlayer::SetupInput(UInputComponent* PlayerInputComponent)
//{
//	
//	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
//	{
//		EnhancedInputComponent->BindAction(AxisInput, ETriggerEvent::Triggered, this, &ABallPlayer::ControlCharacter);
//	}
//
//}


void ABallPlayer::PressedAxis(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D v = Value.Get<FVector2D>();
	
	
	//find out which way is forward向きを得るもの
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//get foward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//get right vector
	const FVector FightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//ワールドに置かれている座標を見ているか(アクター)
	CharacterVector += ForwardDirection * v.Y * Speed;
	this->AddActorLocalOffset(ForwardDirection * v.Y * Speed, true);
	AddActorLocalOffset(FightDirection * v.X * Speed, true);

	
	//スタテックメッシュの座標を見ている(ビューポート上の)
	//コンポーネントの中にある座標
	//Character->AddWorldOffset(ForwardDirection,v.Y);
	//Character->AddWorldOffset(FightDirection,v.X);
	
	////Vectorを計算する
	//FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	//// Characterに力を加える
	//Character->AddForce(ForceVector, NAME_None, true);

	//Axis Input Value
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), v.X, v.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));


}

void ABallPlayer::ControlCharacter(const FInputActionValue& Value)
{
	//inputのValueはVector2Dに変換できる
	FVector2D v = Value.Get<FVector2D>();

	//Vectorを計算する
	FVector ForceVector = FVector(v.Y, v.X, 0.0f) * Speed;

	//Arrowの進行方向のVectorを計算する
	FVector ArrowForceVector = UKismetMathLibrary::TransformDirection(Arrow->GetComponentToWorld(), ForceVector);

	//Characterに力を加える
	Character->AddForce(ForceVector, NAME_Name, true);

}

//Jump関数の作成
void ABallPlayer::Jump(const FInputActionValue& Value)
{
	//inputのvalueはboolに変換できる
	if (const bool v = Value.Get<bool>() && CanJump)
	{
		
		AddActorLocalOffset(FVector(0.0f, 0.0f, JumpImpluse),true);
		Character->AddImpulse(FVector(0.0f, 0.0f, JumpImpluse), TEXT("None"), true);
		CanJump = false;
	}
}

//HitイベントにBindingした関数でCanaJumpを有効にする処理を実装します
void ABallPlayer::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	CanJump = true;

	AddActorWorldOffset(HitNormal);
}

//Event tickの呼び出し
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CapsuleComponent->AddLocalOffset(FVector(0.0f, 0.0f, Under), true);
	AddActorLocalOffset(FVector(0.0f, 0.0f, Under), true);
	
}


//CharacterVelocity()の呼び出し
FVector ABallPlayer::GetForwardDirection()
{
	return CharacterVector;
}

//GetGround()の呼び出し
bool ABallPlayer::GetGround()
{
	return CanJump;
}