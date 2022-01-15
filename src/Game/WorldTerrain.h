#ifndef _WorldTerrain
#define _WorldTerrain

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Frigate;
class WorldTerrain : public GameObject
{
public:
	WorldTerrain();
	~WorldTerrain();

	virtual void Draw() override;
	virtual void Update() override {};
	virtual void Alarm0() override {};

private:
	Model* pTerrain;
	GraphicsObject_TextureFlat* pGObjFT;
	GraphicsObject_ColorNoTexture* pGObjCol;
};

#endif _WorldTerrain