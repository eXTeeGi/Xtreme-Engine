#ifndef _SceneBoss
#define _SceneBoss

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
class BossTank;
class UFO;

class SceneBoss : public Scene
{
public:
	SceneBoss() = default;
	~SceneBoss();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	EnvironmentSpawner* es;
	WorldTerrain* GOPlane;
	Cottage* cottage;
	BossTank* bossTank;
};

#endif _SceneBoss