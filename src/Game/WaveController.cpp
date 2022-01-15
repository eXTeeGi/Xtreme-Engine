#include "WaveController.h"

#include "EnemySpawner.h"
#include "PlayerTankManager.h"
#include "..//Xtreme Engine//XtremeEngine.h"
#include "HUD.h"
#include "SceneBoss.h"
#include "SceneGameTest.h"
#include "Headlines.h"
#include "..//Xtreme Engine/SoundPlayer.h"

WaveController* WaveController::ptrinstance;

WaveController::WaveController() {
	//SubmitKeyRegistration(KEY_1, KeyboardEventManager::KEY_PRESS);
	bTanksGone = false;
	bBossGone = false;
	bRushTanksGone = false;
	bTargetsGone = false;
	currWave = 0;
}

void WaveController::privDelete() {
	delete ptrinstance;
	ptrinstance = nullptr;
}

void WaveController::privSpawnWave(int arg) {
	if (currWave == BossWave) arg = currWave;
	currWave = arg;
	bTanksGone = true;
	bRushTanksGone = true;
	bBossGone = true;
	bTargetsGone = true;
	bUFOsGone = true;

	//PlayerTankManager::positionPlayerTank();
	//PlayerTankManager::respawnPlayer();

	switch (arg)
	{
	case -1:
		bTargetsGone = false;
		HUD::restartTimer();
		XtremeEngine::SetClear(0.8f, 0.7f, 0.6f, 1.0f);
		EnemySpawner::spawnTargetsInCircle(1, 200.0f);
		EnemySpawner::spawnTargetsInCircle(4, 2000.0f);
		
		Headlines::add("WASD to Move.");
		Headlines::add("Left/Right to Look.");
		Headlines::add("Up to Shoot.");
		Headlines::add("Find and shoot the Targets!");
		

		break;
	case 0:
		SceneManager::SetNextScene(new SceneGameTest());
		break;
	case 1:
		XtremeEngine::SetClear(0.6f, 0.9f, 1.0f, 1.0f);
		HUD::restartTimer();
		bTanksGone = false;
		EnemySpawner::spawnTanksInCircle(1);
		
		Headlines::add("Kill the invading tanks!");
		break;
	case 2:
		bTanksGone = false;
		EnemySpawner::spawnTanksInCircle(3);
		Headlines::add("Letter blocks drop ammo and powerups!");

		break;
	case 3:
		bTanksGone = false;
		EnemySpawner::spawnTanksInCircle(5);
		bRushTanksGone = false;
		EnemySpawner::spawnRushTanksInCircle(2);
		Headlines::add("A new enemy type approaches!");


		break;
	case 4:

		XtremeEngine::SetClear(0.1f, 0.1f, 0.1f, 1.0f);
		SoundPlayer::playSound("Cave");
		bUFOsGone = false;
		EnemySpawner::spawnUFOsInCircle(3);
		bRushTanksGone = false;
		EnemySpawner::spawnRushTanksInCircle(2);
		Headlines::add("Hold space for first-person mode!");
		Headlines::add("Use it to shoot the UFOs!");
		break;
	case 5:
		bTanksGone = false;
		EnemySpawner::spawnTanksInCircle(5);
		bUFOsGone = false;
		EnemySpawner::spawnUFOsInCircle(4);
		bRushTanksGone = false;
		EnemySpawner::spawnRushTanksInCircle(2);
		break;
	case BossWave:
		bBossGone = false;
		SceneManager::SetNextScene(new SceneBoss());
		//bRushTanksGone = false;
		
		break;
	default:
		HUD::endTimer();
		break;
	}

	HUD::updateWave(currWave);
}

void WaveController::KeyPressed(AZUL_KEY arg) {
	switch (arg)
	{
	case KEY_1:
		spawnWave(1);
		break;
	default:
		break;
	}
}

void WaveController::privTanksGone() {
	bTanksGone = true;

	isWaveCompleted();
}

void WaveController::privRushTanksGone() {
	bRushTanksGone = true;

	isWaveCompleted();
}

void WaveController::privBossGone() {
	bBossGone = true;

	isWaveCompleted();
}

void WaveController::privTargetsGone() {
	bTargetsGone = true;

	isWaveCompleted();
}

void WaveController::privUFOsGone() {
	bUFOsGone = true;

	isWaveCompleted();
}

bool WaveController::isWaveCompleted() {
	if (bTanksGone == false) return false;
	if (bRushTanksGone == false) return false;
	if (bBossGone == false) return false;
	if (bTargetsGone == false) return false;
	if (bUFOsGone == false) return false;
	if (PlayerTankManager::isPlayerTankAlive() == false) return false;

	if (currWave != 0) SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	return true;
}

void WaveController::Alarm0() {
	spawnWave(++currWave);
}