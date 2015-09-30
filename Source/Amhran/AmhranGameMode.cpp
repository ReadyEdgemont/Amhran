

#include "Amhran.h"
#include "AmhranGameMode.h"


AAmhranGameMode::AAmhranGameMode(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/Player/BP_Amhran_Player.BP_Amhran_Player'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}
}