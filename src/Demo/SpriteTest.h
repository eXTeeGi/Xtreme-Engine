#ifndef _SpriteTest
#define _SpriteTest

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include "..//Xtreme Engine///XtremeSprite.h"
#include "..///Xtreme Engine///SpriteFont.h"
#include "../Xtreme Engine/SpriteString.h"

class WorldPlane;

class SpriteTest : public GameObject
{
public:
	SpriteTest();
	~SpriteTest();

	virtual void Update() override;
	virtual void Draw2D() override;

private:
	XtremeSprite* pGOSprite;
	XtremeSprite* pGOSprite2;
	SpriteFont* fonttest;
	SpriteString* SStest;

};

#endif _SpriteTest