#include "SceneTutorial.h"
#include "PlayerTank.h"
#include "PlayerTankCamera.h"
#include "EnemyTank.h"
#include "..///Demo/WorldPlane.h"
#include "TutorialFloor.h"
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
#include "TrainingTarget.h"
#include "Headlines.h"
#include "UFO.h"

SceneTutorial::~SceneTutorial() {

}

void SceneTutorial::Initialize() {
	PlayerTankManager::spawnPlayer(); 
	//GOTank = new PlayerTank();
	GOPlane = new TutorialFloor();
	//cottage = new Cottage();
	//GOEnemy = new EnemyTank(Vect(50,0,50));
	//GOEnemy = EnemyTankFactory::CreateEnemyTank(Vect(50, 0, 50));
	//GOFence = new Fence();

	es = new EnvironmentSpawner();

	es->generateTutorial();



	WaveController::spawnWave(-1);
	PlayerTankManager::healPlayer();

	SetCollisionPair<PlayerTank, Die>();
	SetCollisionPair<PlayerTank, TrainingTarget>();
	SetCollisionPair<TrainingTarget, Die>();
	SetCollisionPair<PlayerBullet, Die>();
	SetCollisionPair<PlayerBullet, UFO>();
	SetCollisionPair<PlayerBullet, UFO>();
	SetCollisionPair<PlayerTank, UFO>();
	SetCollisionPair<PlayerBullet, EnemyTank>();
	SetCollisionPair<PlayerBullet, TrainingTarget>();
	SetCollisionPair<PlayerTank, AmmoPickup>();
	SetCollisionPair<PlayerTank, Powerup>();
	SetCollisionSelf<Die>();

	HUD::Init();
	
	Headlines::Init();
	//GOSpawner = new EnemySpawner();
	//GOSpawner->startRandomSpawning();
}


void SceneTutorial::SceneEnd() {
	//delete GOTank;
	delete GOPlane;
	//delete cottage;
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