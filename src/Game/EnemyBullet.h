#ifndef _EnemyBullet
#define _EnemyBullet

#include "AzulCore.h"
#include "BulletBase.h"

class Collidable;
class PlayerTank;
class Die;
class Rock;

class EnemyBullet : public BulletBase
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(Matrix, Matrix, Vect);

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);
	virtual void Collision(Die*);
	virtual void Collision(Rock*);
	virtual void SceneExit();

};

#endif _EnemyBullet