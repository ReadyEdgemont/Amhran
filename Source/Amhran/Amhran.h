

#pragma once

#include "Engine.h"

#define DIALOGUE_PATH "dialogue/en/"

//Channel Definitions
#define COLLISION_PROJECTILE    ECC_GameTraceChannel1

//Item Type definitions
#define POTION 0
#define POISION 1
#define WEAPON 2
#define ARMOR 3
#define BOOK 4
#define RUNE 5
#define SCROLL 6
#define MATERIAL 7
#define MISC 8

//Weapon type definitions
#define HSWORD 0
#define HBLUNT 1
#define HHSWORD 2
#define HHBLUNT 3

//Armor type definitions
#define HELMET 0
#define TORSO 1
#define LEGS 2
#define BOOTS 3
#define ARMS 4
#define GLOVES 5
#define RING1 6
#define RING2 7
#define NECKLACE 8

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

#define ALERT_DETECTION_BONUS 1.5

#define NO_PENALTY 1.0
#define CLOSE_PENALTY 0.80
#define NEAR_PENALTY 0.55
#define PROXIMITY_PENALTY 0.25
#define FAR_PENALTY 0.15
#define MAX_PENALTY 0.05

#define MIN_DETECTION_PER_SECOND 0.0 //If below this value per second, no detection will be added
#define INSTANT_DETECTION 130 //If at or above this value/sec, pawn will be instantly detected

#define DETECTION_COOLDOWN 3.5 //Detection lost per second after target leaves view (or detection gain is otherwise below minimum)
