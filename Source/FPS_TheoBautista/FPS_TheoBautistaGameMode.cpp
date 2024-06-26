#include "FPS_TheoBautistaGameMode.h"
#include "FPS_TheoBautistaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_TheoBautistaGameMode::AFPS_TheoBautistaGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
