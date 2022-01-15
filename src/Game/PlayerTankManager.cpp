#include "PlayerTankManager.h"

#include "PlayerTank.h"
#include "EnemyTankFactory.h"
#include "RushTankFactory.h"
#include "UFOFactory.h"
#include "TrainingTargetFactory.h"
#include "WaveController.h"
#include "HUD.h"
#include "PlayerTankRespawnTimer.h"

PlayerTankManager* PlayerTankManager::ptrinstance;

void PlayerTankManager::privSpawnPlayer() {
	if (pTank == nullptr) pTank = new PlayerTank();
	else pTank->SubmitEntry();
}

void PlayerTankManager::privDespawnTank() {
	pTank->SubmitExit();
}

Vect PlayerTankManager::privGetPlayerTankPos() {
	if (pTank != nullptr) return pTank->getPos();
	else return Vect(0, 0, 0);
}

void PlayerTankManager::Delete() {
	Instance().privDelete();

	delete ptrinstance;
	ptrinstance = nullptr;
}

void PlayerTankManager::privDelete() {
	delete pTank;
	pTank = nullptr;
}

void PlayerTankManager::privRespawnTank() {
	delete pTankRT;
	if (WaveController::getWave() != WaveController::BossWave) pTank->SubmitEntry();
	pTank->respawn();
	healPlayer();
	if (WaveController::getWave() == WaveController::BossWave) WaveController::spawnWave(WaveController::BossWave);
	else if (WaveController::getWave() >= 1) WaveController::spawnWave(1);
	else WaveController::spawnWave(-1);
	HUD::updateLives(playerLives);
}

void PlayerTankManager::privDamagePlayer() {
	playerLives -= 1;
	if (playerLives <= 0) {
		EnemyTankFactory::ExitActive();
		RushTankFactory::ExitActive();
		TrainingTargetFactory::ExitActive();
		UFOFactory::ExitActive();
		pTank->SubmitExit();
		pTankRT = new PlayerTankRespawnTimer();
	}
	HUD::updateLives(playerLives);
}

void PlayerTankManager::privHealPlayer() {
	playerLives = maxPlayerLives;
	HUD::updateLives(playerLives);
}

bool PlayerTankManager::privIsPlayerTankAlive() {
	return pTank->isAlive();
}

void PlayerTankManager::privPositionPlayerTank() {
	pTank->respawn();
}

void PlayerTankManager::privPowerupSpeedBoost() {
	pTank->powerupSpeedBoost();
}

void PlayerTankManager::privAbduct() {
	pTank->abduct();
}