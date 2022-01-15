#ifndef _BossTank
#define _BossTank

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class BossTankCamera;
class EnemyTurret;
class PlayerTank;
class PlayerBullet;
class Die;
class Rock;

class BossTank : public GameObject
{
public:
	BossTank();
	~BossTank();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void KeyPressed(AZUL_KEY);

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
	const float maxSpeed = 4.0f;
	const float ShipRotAng = .04f;

	GraphicsObject_TextureLight* pGOTurr;
	Vect TurrPos;
	Matrix TurrRot;
	Matrix TurrScale;
	const float TurrTransSpeed = 1;
	const float TurrRotAng = .02f;

	int lives = 9;

};

#endif _BossTank