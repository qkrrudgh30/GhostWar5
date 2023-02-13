// ZSPawn.cpp

#include "ZSPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"

AZSPawn::AZSPawn()
{
    PrimaryActorTick.bCanEverTick = false;

#pragma region InitializeCapsule
    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

    float CharacterHalfHeight = 177.f;
    float CharacterRadius = 25.f;
    Capsule->SetCapsuleHalfHeight(CharacterHalfHeight);
    Capsule->SetCapsuleRadius(CharacterRadius);
#pragma endregion

#pragma region InitializeSkeletalMesh
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETALMESH"));

    FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
    FRotator PivotRotation(0.f, -90.f, 0.f);
    SkeletalMesh->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
    if (true == SK_BODY.Succeeded())
    {
        SkeletalMesh->SetSkeletalMesh(SK_BODY.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> BP_PLAYERANIMBLUEPRINT(TEXT("AnimBlueprint'/Game/AnimationBlueprints/PlayerAnimBlueprint.PlayerAnimBlueprint_C'"));
    if (true == BP_PLAYERANIMBLUEPRINT.Succeeded())
    {
        SkeletalMesh->SetAnimInstanceClass(BP_PLAYERANIMBLUEPRINT.Class);
    }

#pragma endregion

#pragma region InitializeSpringArm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));

    float SpringArmLength = 400.f;
    SpringArm->TargetArmLength = SpringArmLength;
    
    float SpringArmRotationPitch = -15.f;
    FRotator SpringArmRotation({ SpringArmRotationPitch, 0.f, 0.f });
    SpringArm->SetRelativeRotation(SpringArmRotation);
#pragma endregion

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

    RootComponent = Capsule;
    SkeletalMesh->SetupAttachment(RootComponent);
    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);

}

void AZSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AZSPawn::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AZSPawn::LeftRight);
}

void AZSPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AZSPawn::UpDown(float NewAxisValue)
{
    AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AZSPawn::LeftRight(float NewAxisValue)
{
    AddMovementInput(GetActorRightVector(), NewAxisValue);
}

