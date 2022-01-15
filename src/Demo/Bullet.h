#ifndef _Bullet
#define _Bullet

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	//Bullet(Matrix, Matrix, Vect);
	~Bullet();

	void Initialize(Matrix, Matrix, Vect);

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Alarm0() override;

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	GraphicsObject_WireframeConstantColor* pGObjLT;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;
	const float ShipTransSpeed = 2;
	const float ShipRotAng = .05f;
};

#endif _Bullet