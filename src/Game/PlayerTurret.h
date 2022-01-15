#ifndef _PlayerTurret
#define _PlayerTurret

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class PlayerTankCamera;
class FPSCamera;

class PlayerTurret : public GameObject
{
public:
	PlayerTurret();
	~PlayerTurret();

	virtual void Update() override;
	virtual void Draw() override;

	void MyUpdate(Vect);

	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void KeyPressed(AZUL_KEY);

	virtual void Alarm0();

	void respawn();

	void addAmmo(int n);
	PlayerTankCamera* getCam() { return cam; };
	FPSCamera* getFPSCam() { return fpscam; };
private:
	GraphicsObject_TextureLight* pGO;
	PlayerTankCamera* cam;
	FPSCamera* fpscam;
	Vect TurrPos;
	Matrix TurrRot;
	Matrix TurrScale;
	const float TurrTransSpeed = 1;
	const float TurrRotAng = .02f;
	int ammo = 100;
	bool canShoot = true;
};

#endif _PlayerTurret