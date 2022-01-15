#ifndef _GameController
#define _GameController

#include "AzulCore.h"

class PlayerTank;

class GameController
{
public:
	static GameController* ptrinstance;

	static void spawnPlayer() { Instance().privSpawnPlayer(); };
	static void despawnPlayer() { Instance().privDespawnTank(); }
	static Vect getPlayerTankPos() { return Instance().privGetPlayerTankPos(); };
	static void Delete() { Instance().privDelete(); }
	static void respawnPlayer() { Instance().privRespawnTank(); }

private:
	static GameController& Instance() {
		if (!ptrinstance)
			ptrinstance = new GameController;
		return *ptrinstance;
	}

	void privSpawnPlayer();
	void privDespawnTank();
	Vect privGetPlayerTankPos();
	void privDelete();
	void privRespawnTank();

	PlayerTank* pTank = nullptr;
};

#endif _GameController