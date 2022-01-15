#ifndef _Rock
#define _Rock

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <list>

class PlayerBullet;
class PlayerTank;
class EnemyBullet;

class Rock : public GameObject
{
public:
	Rock();
	Rock(Vect pos);
	~Rock();

	virtual void Draw();
	virtual void Update();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerBullet*) {};
	virtual void Collision(EnemyBullet*) {};
	virtual void Collision(PlayerTank*) {};

	Vect getPos() { return pos; }
private:
	Vect pos;
	Matrix rot;
	Matrix scale;
	GraphicsObject_TextureLight* pGO;
};

#endif _Rock