// ZSGameMode.cpp

#include "ZSGameMode.h"
#include "ZSPlayerController.h"
#include "ZSPawn.h"

AZSGameMode::AZSGameMode()
{
    PlayerControllerClass = AZSPlayerController::StaticClass();
    DefaultPawnClass = AZSPawn::StaticClass();    
}
