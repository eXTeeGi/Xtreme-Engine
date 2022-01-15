#include "SceneBoss.h"
#include "PlayerTank.h"
#include "PlayerTankCamera.h"
#include "EnemyTank.h"
#include "..///Demo/WorldPlane.h"
#include "WorldTerrain.h"
#include "..//Xtreme Engine/CameraManager.h"
#include "PlayerTankManager.h"
#include "EnemySpawner.h"
#include "EnemyTankFactory.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Fence.h"
#include "WaveController.h"
#include "PlayerTankManager.h"
#include "HUD.h"
#include "Cottage.h"
#include "Die.h"
#include "Rock.h"
#include "RushTank.h"
#include "EnvironmentSpawner.h"
#include "AmmoPickup.h"
#include "Powerup.h"
#include "BossTank.h"
#include "UFO.h"
#include "Headlines.h"

SceneBoss::~SceneBoss() {

}

void SceneBoss::Initialize() {
	PlayerTankManager::spawnPlayer();
	GOPlane = new WorldTerrain();
	cottage = new Cottage();
	bossTank = new BossTank();

	es = new EnvironmentSpawner();

	es->generateBoss();



	//WaveController::spawnWave(1);
	//PlayerTankManager::healPlayer();

	SetCollisionPair<PlayerTank, EnemyBullet>();
	SetCollisionPair<PlayerTank, Die>();
	SetCollisionPair<PlayerTank, BossTank>();
	SetCollisionPair<BossTank, Die>();
	SetCollisionPair<PlayerBullet, RushTank>();
	SetCollisionPair<PlayerBullet, Die>();
	SetCollisionPair<PlayerBullet, UFO>();
	SetCollisionPair<PlayerTank, UFO>();
	SetCollisionPair<PlayerBullet, BossTank>();
	SetCollisionPair<EnemyBullet, Die>();
	SetCollisionPair<PlayerTank, RushTank>();
	SetCollisionPair<PlayerTank, AmmoPickup>();
	SetCollisionPair<PlayerTank, Powerup>();
	SetCollisionSelf<Die>();

	HUD::Init();
	Headlines::Init();

	//EnemySpawner::spawnRushTanksInCircle(3);
	Headlines::add("It's... you?");

}


void SceneBoss::SceneEnd() {
	HUD::endScene();
	Headlines::endScene();

	//PlayerTankManager::despawnPlayer();

	delete GOPlane;
	delete cottage;
	delete bossTank;
	//delete GOFence;
	//delete GOEnemy;

	delete es;

	//PlayerTankManager::despawnPlayer();

}