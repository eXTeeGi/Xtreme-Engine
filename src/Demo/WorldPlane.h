#ifndef _WorldPlane
#define _WorldPlane

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Frigate;
class WorldPlane: public GameObject
{
public:
	WorldPlane();
	 ~WorldPlane();

	virtual void Draw() override;
	virtual void Update() override {};
	virtual void Alarm0() override {};

	virtual void Collision(Collidable*) {};
	virtual void Collision(Frigate*) {
		//DebugMsg::out("Collision WorldPlane with Frigate\n");
	};
	virtual void Collision(WorldPlane*) {
		//DebugMsg::out("Collision WorldPlane with WorldPlane\n");
	};

	virtual void KeyPressed(AZUL_KEY);
	virtual void KeyReleased(AZUL_KEY);

private:
	GraphicsObject_TextureFlat* pGObjFT;
	GraphicsObject_ColorNoTexture* pGObjCol;
};

#endif _WorldPlane