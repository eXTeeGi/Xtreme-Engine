#ifndef _SceneDemo
#define _SceneDemo

#include "AzulCore.h"
#include "../Xtreme Engine/Scene.h"

class Frigate;
class WorldPlane;
class SpriteTest;
class TerrainDemo;

class SceneDemo : public Scene
{
public:
	SceneDemo() = default;
	~SceneDemo() {};

	virtual void Initialize();
	virtual void SceneEnd();

private:
	Frigate* GOFrig;
	WorldPlane* GOPlane;
	SpriteTest* GOsprite;
	//TerrainDemo* pT;
};

#endif _SceneDemo