#ifndef _TutorialFloor
#define _TutorialFloor

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Frigate;
class TutorialFloor : public GameObject
{
public:
	TutorialFloor();
	~TutorialFloor();

	virtual void Draw() override;
	virtual void Update() override {};
	virtual void Alarm0() override {};

private:
	Model* pTerrain;
	GraphicsObject_TextureFlat* pGObjFT;
	GraphicsObject_ColorNoTexture* pGObjCol;
};

#endif _TutorialFloor