#ifndef _WaveController
#define _WaveController

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class WaveController: public GameObject
{
public:
	static WaveController* ptrinstance;

	static void Delete() { Instance().privDelete(); }

	static void spawnWave(int waveNum) {Instance().privSpawnWave(waveNum);};

	static void tanksGone() { Instance().privTanksGone(); };
	static void rushTanksGone() { Instance().privRushTanksGone(); };
	static void bossGone() { Instance().privBossGone(); };
	static void targetsGone() { Instance().privTargetsGone(); };
	static void UFOsGone() {Instance().privUFOsGone();};

	static int getWave() { return Instance().currWave; }

	static const int BossWave = 6;
private:
	static WaveController& Instance() {
		if (!ptrinstance)
			ptrinstance = new WaveController;
		return *ptrinstance;
	}

	WaveController();
	~WaveController() = default;

	virtual void KeyPressed(AZUL_KEY);
	virtual void Alarm0();

	void privDelete();
	void privSpawnWave(int arg);

	void privTanksGone();
	void privRushTanksGone();
	void privBossGone();
	void privTargetsGone();
	void privUFOsGone();

	bool isWaveCompleted();

	int currWave;
	bool bTanksGone;
	bool bRushTanksGone;
	bool bBossGone;
	bool bTargetsGone;
	bool bUFOsGone;

};

#endif _WaveController