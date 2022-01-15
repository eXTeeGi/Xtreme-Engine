#ifndef _EnemySpawner
#define _EnemySpawner

#include "AzulCore.h"
#include "..//Xtreme Engine/GameObject.h"

class EnemyTank;

class EnemySpawner: public GameObject
{
public:
	static EnemySpawner* ptrinstance;


	

	static void Delete();

	static void startRandomSpawning() { Instance().privStartRandomSpawning(); };
	static void stopRandomSpawning() { Instance().privStopRandomSpawning(); };

	static void spawnTanksInCircle(int numTanks,float radius = 3000.0f) { Instance().privSpawnTanksInCircle(numTanks, radius); };
	static void spawnRushTanksInCircle(int numTanks, float radius = 3000.0f) { Instance().privSpawnRushTanksInCircle(numTanks, radius); };
	static void spawnTargetsInCircle(int numTargets, float radius = 3000.0f) { Instance().privSpawnTargetsInCircle(numTargets, radius); };
	static void spawnUFOsInCircle(int numUFO,float radius = 3000.0f) { Instance().privSpawnUFOsInCircle(numUFO, radius); };
	

private:
	static EnemySpawner& Instance() {
		if (!ptrinstance)
			ptrinstance = new EnemySpawner;
		return *ptrinstance;
	}

	EnemySpawner();

	virtual void Update();
	virtual void Draw();

	virtual void Alarm0();

	void privDelete();

	void privStartRandomSpawning();
	void privStopRandomSpawning();

	void privSpawnTanksInCircle(int numTanks,float radius);
	void privSpawnRushTanksInCircle(int numTanks, float radius);
	void privSpawnTargetsInCircle(int numTanks, float radius);
	void privSpawnUFOsInCircle(int numUFO,float radius);
};

#endif _EnemySpawner