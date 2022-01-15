#ifndef _SceneGameTest
#define _SceneGameTest

#include "AzulCore.h"
#include "../Xtreme Engine/Scene.h"

class WorldPlane;
class PlayerTank;
class PlayerTankCamera;
class EnemyTank;
class EnemySpawner;
class WorldTerrain;
class Fence;
class Cottage;
class EnvironmentSpawner;
class Die;
class UFO;


class SceneGameTest : public Scene
{
public:
	SceneGameTest() = default;
	~SceneGameTest();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	//PlayerTank* GOTank;
	EnvironmentSpawner* es;
	WorldTerrain* GOPlane;
	EnemyTank* GOEnemy;
	EnemySpawner* GOSpawner;
	Fence* GOFence;
	Cottage* cottage;
	
};

#endif _SceneGameTest