#ifndef _EnemyTank
#define _EnemyTank

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class EnemyTankCamera;
class EnemyTurret;
class PlayerTank;
class PlayerBullet;
class Die;
class Rock;

class EnemyTank : public GameObject
{
public:
	EnemyTank() = delete;
	EnemyTank(Vect pos);
	~EnemyTank();

	void Initialize(Vect pos);

	virtual void Update() override;
	virtual void Draw() override;
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void Alarm2();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);
	virtual void Collision(PlayerBullet*);
	virtual void Collision(Die*);
	virtual void Collision(Rock*);

	Vect& getPos() { return ShipPos; }


private:
	GraphicsObject_TextureLight* pGO;
	//EnemyTurret* turret;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;

	float ShipTransSpeed = 0.0f;
	const float maxSpeed = 3.0f;
	const float ShipRotAng = .04f;

	GraphicsObject_TextureLight* pGOTurr;
	Vect TurrPos;
	Matrix TurrRot;
	Matrix TurrScale;
	const float TurrTransSpeed = 1;
	const float TurrRotAng = .01f;

	//simulate input
	int WorS = 0;
	int AorD = 0;
};

#endif _EnemyTank