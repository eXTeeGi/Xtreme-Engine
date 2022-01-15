#ifndef _UFO
#define _UFO

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class PlayerBullet;

class UFO : public GameObject
{
public:
	UFO() = delete;
	UFO(Vect pos);
	~UFO();

	void Initialize(Vect pos);

	virtual void Update() override;
	virtual void Draw() override;
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerBullet*);

	Vect& getPos() { return ShipPos; }

private:
	GraphicsObject_TextureLight* pGO;
	//EnemyTurret* turret;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;
	int xDir = 1;
	int zDir = 1;

	float ShipTransSpeed = 2.0f;

};

#endif _UFO