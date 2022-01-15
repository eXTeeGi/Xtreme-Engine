#include "PowerupManager.h"

#include "PlayerTankManager.h"
#include "Headlines.h"
#include "..//Xtreme Engine/SoundPlayer.h"

PowerupManager* PowerupManager::ptrinstance;


PowerupManager::PowerupManager() {
	powerupProbability = 3;
}

void PowerupManager::privTerminate() {
	delete ptrinstance;
	ptrinstance = nullptr;
}

void PowerupManager::speedBoost() {
	PlayerTankManager::powerupSpeedBoost();
	SoundPlayer::playSound("Boost");
	Headlines::add("Speed Boost!");
}