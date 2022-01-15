#ifndef _RushTank
#define _RushTank

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class RushTankCamera;
class EnemyTurret;
class PlayerTank;
class PlayerBullet;

class RushTank : public GameObject
{
public:
	RushTank() = delete;
	RushTank(Vect pos);
	~RushTank();

	void Initialize(Vect pos);

	virtual void Update() override;
	virtual void Draw() override;
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);
	virtual void Collision(PlayerBullet*);

private:
	GraphicsObject_TextureLight* pGO;
	//EnemyTurret* turret;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;

	float ShipTransSpeed = 0.0f;
	const float maxSpeed = 1.0f;
	const float ShipRotAng = .01f;

	GraphicsObject_TextureLight* pGOTurr;
	Vect TurrPos;
	Matrix TurrRot;
	Matrix TurrScale;
	const float TurrTransSpeed = 1;
	const float TurrRotAng = .01f;

	int lives = 3;

};

#endif _RushTank