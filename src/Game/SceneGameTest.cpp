#include "SceneGameTest.h"
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
#include "UFO.h"
#include "Headlines.h"

SceneGameTest::~SceneGameTest() {

}

void SceneGameTest::Initialize() {
	PlayerTankManager::spawnPlayer();
	//GOTank = new PlayerTank();
	GOPlane = new WorldTerrain();
	cottage = new Cottage();
	//GOEnemy = new EnemyTank(Vect(50,0,50));
	//GOEnemy = EnemyTankFactory::CreateEnemyTank(Vect(50, 0, 50));
	//GOFence = new Fence();
	
	es = new EnvironmentSpawner();

	es->generate();

	

	WaveController::spawnWave(1);
	PlayerTankManager::healPlayer();

	SetCollisionPair<PlayerTank, EnemyTank>();
	SetCollisionPair<PlayerTank, EnemyBullet>();
	SetCollisionPair<PlayerTank, Die>();
	SetCollisionPair<EnemyTank, Die>();
	SetCollisionPair<PlayerTank, Rock>();
	SetCollisionPair<EnemyTank, Rock>();
	SetCollisionPair<PlayerBullet, EnemyTank>();
	SetCollisionPair<PlayerBullet, RushTank>();
	SetCollisionPair<PlayerBullet, Die>();
	SetCollisionPair<Rock, Die>();
	SetCollisionPair<EnemyBullet, Die>();
	SetCollisionPair<PlayerBullet, Rock>();
	SetCollisionPair<PlayerBullet, UFO>();
	SetCollisionPair<PlayerTank, UFO>();
	SetCollisionPair<EnemyBullet, Rock>();
	SetCollisionPair<PlayerTank, RushTank>();
	SetCollisionPair<PlayerTank, AmmoPickup>();
	SetCollisionPair<PlayerTank, Powerup>();
	SetCollisionSelf<Die>();

	HUD::Init();
	Headlines::Init();
	//GOSpawner = new EnemySpawner();
	//GOSpawner->startRandomSpawning();
}


void SceneGameTest::SceneEnd() {
	//delete GOTank;
	delete GOPlane;
	delete cottage;
	//delete GOFence;
	//delete GOEnemy;

	delete es;

	//EnemySpawner::stopRandomSpawning();
	//GOSpawner->stopRandomSpawning();
	//delete GOSpawner;
	HUD::endScene();
	Headlines::endScene();
	PlayerTankManager::despawnPlayer();
}