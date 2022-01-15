#ifndef _PlayerTank
#define _PlayerTank

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class PlayerTurret;
class PlayerTankCamera;
class EnemyTank;
class EnemyBullet;
class RushTank;
class Die;
class Rock;
class AmmoPickup;
class Powerup;
class UFO;
class BossTank;
class TrainingTarget;

class PlayerTank : public GameObject
{
public:
	PlayerTank();
	~PlayerTank();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void KeyPressed(AZUL_KEY);
	virtual void KeyReleased(AZUL_KEY);

	virtual void Collision(Collidable*) {};
	virtual void Collision(EnemyTank*);
	virtual void Collision(UFO*);
	virtual void Collision(BossTank*);
	virtual void Collision(RushTank*);
	virtual void Collision(Die*);
	virtual void Collision(EnemyBullet*);
	virtual void Collision(Rock*);
	virtual void Collision(AmmoPickup*);
	virtual void Collision(Powerup*);
	virtual void Collision(TrainingTarget*);

	virtual void Alarm0(); //speed boost timer
	void powerupSpeedBoost();

	Vect getPos() { return ShipPos; };

	void respawn();
	bool isAlive();

	void abduct();

private:
	GraphicsObject_TextureLight* pGO;
	PlayerTurret* turret;
	PlayerTankCamera* cam;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;
	float ShipTransSpeed = 0.0f;
	const float maxSpeed = 3.0f;
	const float ShipRotAng = .04f;
	bool BsphereToggle = false;
	int speedBoosted = 1;
	bool beingAbducted;
};

#endif _PlayerTank