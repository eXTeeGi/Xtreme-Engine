#ifndef _BulletBase
#define _BulletBase

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class BulletBase : public GameObject
{
public:
	BulletBase();
	virtual ~BulletBase();

	

	virtual void Update() override;
	virtual void Draw() override;

	virtual void SceneEntry();
protected:
	GraphicsObject_WireframeConstantColor* pGObjLT;
	Vect ShipPos;
	Matrix ShipRot;
	
	Matrix ShipScale;
	float ShipTransSpeed = 5;
	const float ShipRotAng = .05f;
};

#endif _BulletBase