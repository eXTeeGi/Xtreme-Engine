#ifndef _AmmoPickup
#define _AmmoPickup

#include "Pickup.h"

class PlayerTank;

class AmmoPickup : public Pickup
{
public:
	AmmoPickup();
	AmmoPickup(float x, float z);
	~AmmoPickup();
	AmmoPickup(const AmmoPickup&) = delete;
	AmmoPickup& operator=(const AmmoPickup&) = delete;

	void Initialize(Vect pos);

	virtual void Update();
	virtual void Draw();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);

	virtual void SceneExit();
private:
	GraphicsObject_TextureLight* pGO;
	Vect Pos;
	Matrix Rot;
	Matrix Scale;
};

#endif _AmmoPickup