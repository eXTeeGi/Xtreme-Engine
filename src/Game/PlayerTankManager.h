#ifndef _PlayerTankManager
#define _PlayerTankManager

#include "AzulCore.h"

class PlayerTank;
class PlayerTankRespawnTimer;

class PlayerTankManager
{
public:
	static PlayerTankManager* ptrinstance;

	static void spawnPlayer() { Instance().privSpawnPlayer(); };
	static void despawnPlayer() { Instance().privDespawnTank(); }
	static Vect getPlayerTankPos() { return Instance().privGetPlayerTankPos(); };
	static void Delete();
	static void respawnPlayer() { Instance().privRespawnTank(); }
	static void healPlayer() { Instance().privHealPlayer(); }
	static void damagePlayer() { Instance().privDamagePlayer(); }
	static bool isPlayerTankAlive() { return Instance().privIsPlayerTankAlive(); }
	static void positionPlayerTank() { Instance().privPositionPlayerTank(); }
	static int getLives() { return Instance().playerLives; }
	static void powerupSpeedBoost() { Instance().privPowerupSpeedBoost(); }
	static void abduct() { Instance().privAbduct(); }

private:
	static PlayerTankManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new PlayerTankManager;
		return *ptrinstance;
	}

	void privSpawnPlayer();
	void privDespawnTank();
	Vect privGetPlayerTankPos();
	void privDelete();
	void privRespawnTank();
	void privDamagePlayer();
	void privHealPlayer();
	bool privIsPlayerTankAlive();
	void privPositionPlayerTank();
	void privPowerupSpeedBoost();
	void privAbduct();

	PlayerTank* pTank = nullptr;
	PlayerTankRespawnTimer* pTankRT = nullptr;
	int playerLives;
	static const int maxPlayerLives = 3;
};

#endif _PlayerTankManager