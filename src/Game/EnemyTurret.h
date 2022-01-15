#ifndef _EnemyTurret
#define _EnemyTurret

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"


class EnemyTurret : public GameObject
{
public:
	EnemyTurret();
	~EnemyTurret();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Alarm0();

	void MyUpdate(Vect);

	virtual void SceneEntry();

private:
	GraphicsObject_WireframeConstantColor* pGO;
	Vect TurrPos;
	Matrix TurrRot;
	Matrix TurrScale;
	const float TurrTransSpeed = 1;
	const float TurrRotAng = .01f;
};

#endif _EnemyTurret