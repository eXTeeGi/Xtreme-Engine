#ifndef _SceneTutorial
#define _SceneTutorial

#include "AzulCore.h"
#include "../Xtreme Engine/Scene.h"

class WorldPlane;
class PlayerTank;
class PlayerTankCamera;
class EnemySpawner;
class TutorialFloor;
class Fence;
class Cottage;
class EnvironmentSpawner;
class Die;
class TrainingTarget;
class UFO;


class SceneTutorial : public Scene
{
public:
	SceneTutorial() = default;
	~SceneTutorial();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	//PlayerTank* GOTank;
	EnvironmentSpawner* es;
	TutorialFloor* GOPlane;
	//EnemyTank* GOEnemy;
	EnemySpawner* GOSpawner;
	//Fence* GOFence;
	//Cottage* cottage;

};

#endif _SceneTutorial