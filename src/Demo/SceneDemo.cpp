#include "SceneDemo.h"
#include "Frigate.h"
#include "WorldPlane.h"
#include "SpriteTest.h"
#include "TerrainDemo.h"

void SceneDemo::Initialize() {
	SetTerrain("Test");

	GOFrig = new Frigate();
	GOPlane = new WorldPlane();
	GOsprite = new SpriteTest();

	//pT = new TerrainDemo();

	SetCollisionPair<Frigate, WorldPlane>();
	SetCollisionSelf<Frigate>();
	SetCollisionTerrain<Frigate>();
}


void SceneDemo::SceneEnd() {
	delete GOFrig;
	delete GOPlane;
	delete GOsprite;
	//delete pT;
}