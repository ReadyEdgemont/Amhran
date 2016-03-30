

#pragma once

#include "Engine.h"

#define DIALOGUE_PATH "dialogue/en/"

DECLARE_LOG_CATEGORY_EXTERN(GeneralLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ErrorLog, Log, All);

UENUM(BlueprintType)
enum class EItemTypeEnum : uint8
{
	Weapon		UMETA(DisplayName = "Weapon"),
	Armor 		UMETA(DisplayName = "Armor"),
	Potion		UMETA(DisplayName = "Potion"),
	Book		UMETA(DisplayName = "Book"),
	Rune		UMETA(DisplayName = "Rune"),
	Scroll		UMETA(DisplayName = "Scroll"),
	Material	UMETA(DisplayName = "Material"),
	Misc		UMETA(DisplayName = "Misc")
};

UENUM(BlueprintType)
enum class EWeaponTypeEnum : uint8
{
	HSword		UMETA(DisplayName = "One-Handed Sword"),
	HHSword 	UMETA(DisplayName = "Two-Handed Sword"),
	HBlunt		UMETA(DisplayName = "One-Handed Blunt"),
	HHBlunt		UMETA(DisplayName = "Two-Handed Blunt")
};

UENUM(BlueprintType)
enum class EArmorTypeEnum : uint8
{
	Helmet		UMETA(DisplayName = "Helmet"),
	Curaiss 	UMETA(DisplayName = "Curaiss"),
	Greaves		UMETA(DisplayName = "Greaves"),
	Boots		UMETA(DisplayName = "Boots"),
	Gauntlets	UMETA(DisplayName = "Gauntlets"),
	Gloves		UMETA(DisplayName = "Gloves"),
	Ring		UMETA(DisplayName = "Ring"),
	Amulet		UMETA(DisplayName = "Amulet")
};

//Channel Definitions
#define COLLISION_PROJECTILE    ECC_GameTraceChannel1

//AI Detection Values
#define TIGHT_DETECTION_CONE 25.0
#define MID_DETECTION_CONE 50.0
#define LOOSE_DETECTION_CONE 75.0

#define TIGHT_PENALTY 130.0
#define MID_PENALTY 80.0
#define LOOSE_PENALTY 50.0

#define DISTANCE_BEGIN_DROPOFF 250
#define CLOSE 600
#define NEAR 1200
#define PROXIMITY 2700
#define FAR 4500
#define MAX_DETECTION_RANGE 7000

#define ALERT_DETECTION_BONUS 1.5	//Once an NPC is alerted, this is their new detection speed (1.0 normal)

#define NO_PENALTY 1.0
#define CLOSE_PENALTY 0.80
#define NEAR_PENALTY 0.55
#define PROXIMITY_PENALTY 0.25
#define FAR_PENALTY 0.15
#define MAX_PENALTY 0.05

#define MIN_DETECTION_PER_SECOND 0.0 //If below this value per second, no detection will be added
#define INSTANT_DETECTION 130 //If at or above this value/sec, character will be instantly detected

#define DETECTION_COOLDOWN 3.5 //Detection lost per second after target leaves view (or detection gain is otherwise below minimum)

const double SKILL_EXP_GROWTH = 1.65;
const int32 SKILL_MULT_GROWTH = 3;
const int32 SKILL_OFFSET = 65;

#define DEFAULT_WEAPON_SKILL_DMG_MOD 0.03	// Default % damage boost to weapons per level in appropriate skill.		0.03 = 3% / level

#define ABILITY_DEFAULT_VALUE 10			//Default value for ability scores (STR, CON, DEX, etc.)
#define SKILL_DEFAULT_VALUE 1

#define DEFAULT_WEAPON_DAMAGE 10
#define DEFAULT_WEAPON_SPEED 1
#define DEFAULT_WEAPON_RANGE 200