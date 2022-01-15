#ifndef _SpeedBoost
#define _SpeedBoost

#include "Pickup.h"

class PlayerTank;

class Powerup : public Pickup
{
private:
	enum PowerupType {
		SPEEDBOOST
	};
public:


	Powerup();
	~Powerup();
	Powerup(const Powerup&) = delete;
	Powerup& operator=(const Powerup&) = delete;

	void Initialize(Vect pos);

	virtual void Update();
	virtual void Draw();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);

	virtual void SceneExit();
private:
	GraphicsObject_TextureLight* pGOCurr;
	GraphicsObject_TextureLight* pGOSpeed;
	Vect Pos;
	Matrix Rot;
	Matrix Scale;
	PowerupType type;
};

#endif _SpeedBoost