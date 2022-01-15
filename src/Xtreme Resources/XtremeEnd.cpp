#include "..//Xtreme Engine/XtremeEngine.h"
#include "..//Demo/BulletFactory.h"
#include "..//Game/PlayerTankManager.h"
#include "..//Game/EnemyTankFactory.h"
#include "..//Game/RushTankFactory.h"
#include "..//Game/PlayerBulletFactory.h"
#include "..//Game/EnemyBulletFactory.h"
#include "..//Game/AmmoPickupFactory.h"
#include "..//Game/PowerupFactory.h"
#include "..//Game/UFOFactory.h"
#include "..//Game/TrainingTargetFactory.h"
#include "..//Game/EnemySpawner.h"
#include "..//Game/WaveController.h"
#include "..//Game/HUD.h"
#include "..//Game/Headlines.h"
#include "..//Game/PowerupManager.h"

void XtremeEngine::XtremeEnd() {
	BulletFactory::Terminate();
	UFOFactory::Terminate();
	EnemyTankFactory::Terminate();
	RushTankFactory::Terminate();
	PlayerBulletFactory::Terminate();
	EnemyBulletFactory::Terminate();
	TrainingTargetFactory::Terminate();
	PlayerTankManager::Delete();
	EnemySpawner::Delete();
	WaveController::Delete();
	AmmoPickupFactory::Terminate();
	PowerupFactory::Terminate();
	Headlines::Terminate();
	PowerupManager::Terminate();
	HUD::Delete();
}