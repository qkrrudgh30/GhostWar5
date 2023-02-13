// ZSPawn.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ZSPawn.generated.h"

UCLASS()
class ZOMBIESURVIVAL_API AZSPawn : public APawn
{
    GENERATED_BODY()

public:
    AZSPawn();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

private:
    void UpDown(float NewAxisValue);
    void LeftRight(float NewAxisValue);

private:
    UPROPERTY(VisibleAnywhere, Category=Collision, meta=(AllowPrivateAccess=true));
    class UCapsuleComponent* Capsule;

    UPROPERTY(VisibleAnywhere, Category=Collision, meta=(AllowPrivateAccess=true));
    class USkeletalMeshComponent* SkeletalMesh;

    UPROPERTY(VisibleAnywhere, Category=Collision, meta=(AllowPrivateAccess=true));
    class UFloatingPawnMovement* PawnMovement;

    UPROPERTY(VisibleAnywhere, Category=Collision, meta=(AllowPrivateAccess=true));
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category=Collision, meta=(AllowPrivateAccess=true));
    class UCameraComponent* Camera;


};
