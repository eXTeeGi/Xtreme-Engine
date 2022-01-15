#ifndef _PlayerBullet
#define _PlayerBullet

#include "AzulCore.h"
#include "BulletBase.h"

class Collidable;
class EnemyTank;
class RushTank;
class Die;
class BossTank;
class Rock;
class TrainingTarget;
class UFO;

class PlayerBullet : public BulletBase
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize(Matrix, Matrix, Vect);

	virtual void Collision(Collidable*) {};
	virtual void Collision(EnemyTank*);
	virtual void Collision(RushTank*);
	virtual void Collision(BossTank*);
	virtual void Collision(Die*);
	virtual void Collision(Rock*);
	virtual void Collision(UFO*);
	virtual void Collision(TrainingTarget*);
	virtual void SceneExit();

};

#endif _PlayerBullet