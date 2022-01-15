

#ifndef _EnemyBulletFactory
#define _EnemyBulletFactory

#include "EnemyBulletObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class EnemyBulletFactory
{
private:
	EnemyBulletFactory() = default;
	EnemyBulletFactory(const EnemyBulletFactory&) = delete;
	EnemyBulletFactory& operator=(const EnemyBulletFactory&) = delete;
	~EnemyBulletFactory() = default;

	static EnemyBulletFactory* ptrInstance;
	static EnemyBulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBulletFactory();
		return *ptrInstance;
	};

	EnemyBulletObjectPool myEnemyBulletPool;

	void privCreateEnemyBullet(Matrix, Matrix, Vect);
	void privRecycleEnemyBullet(GameObject* b);

	int maxAmmo = 999;
	int ammo = maxAmmo;

public:

	static void CreateEnemyBullet(Matrix a, Matrix b, Vect c) { Instance().privCreateEnemyBullet(a, b, c); };
	static void RecycleEnemyBullet(GameObject* b) { Instance().privRecycleEnemyBullet(b); };

	static void Terminate();
};


#endif _EnemyBulletFactory