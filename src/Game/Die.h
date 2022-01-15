#ifndef _Die
#define _Die

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <list>

class PlayerBullet;
class PlayerTank;
class Rock;
class EnemyBullet;
class BossTank;
class EnemyTank;
class TrainingTarget;

class Die : public GameObject
{
public:
	Die();
	Die(Vect pos);
	~Die();

	virtual void Draw();
	virtual void Update();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerBullet*);
	virtual void Collision(EnemyBullet*);
	virtual void Collision(PlayerTank*);
	virtual void Collision(BossTank*);
	virtual void Collision(EnemyTank*);
	virtual void Collision(Die*);
	virtual void Collision(Rock*);
	virtual void Collision(TrainingTarget*);

	virtual void SceneExit();
	virtual void SceneEntry();

	Vect getPos() { return pos; }
private:
	static int powerupProbability;
	int HP;
	Vect pos;
	Matrix rot;
	Matrix scale;
	GraphicsObject_TextureLight* pGO;
};

#endif _Die