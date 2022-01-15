#include "GameController.h"

#include "PlayerTank.h"

GameController* GameController::ptrinstance;

void GameController::privSpawnPlayer() {
	if (pTank == nullptr) pTank = new PlayerTank();
	else pTank->SubmitEntry();
}

void GameController::privDespawnTank() {
	pTank->SubmitExit();
}

Vect GameController::privGetPlayerTankPos() {
	if (pTank != nullptr) return pTank->getPos();
	else return Vect(0, 0, 0);
}

void GameController::privDelete() {
	delete pTank;
	pTank = nullptr;

	delete ptrinstance;
	ptrinstance = nullptr;
}

void GameController::privRespawnTank() {
	pTank->respawn();
}