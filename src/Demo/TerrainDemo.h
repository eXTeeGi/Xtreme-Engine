#ifndef _TerrainDemo
#define _TerrainDemo

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class WorldPlane;
class TerrainObject;
class Frigate;

class TerrainDemo : public GameObject
{
public:
	TerrainDemo();
	~TerrainDemo();

	virtual void Update() override;
	virtual void Draw() override;


private:
	Frigate* GOFrig;
	TerrainObject* pModel;
	GraphicsObject_TextureLight* pGO;
	GraphicsObject_WireframeConstantColor* pWF;
};

#endif _TerrainDemo