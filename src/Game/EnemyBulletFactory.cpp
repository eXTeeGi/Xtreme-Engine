

#include "EnemyBulletFactory.h"
#include "EnemyBulletObjectPool.h"
#include "EnemyBullet.h"

EnemyBulletFactory* EnemyBulletFactory::ptrInstance = nullptr;

void EnemyBulletFactory::privCreateEnemyBullet(Matrix a, Matrix b, Vect c)
{
	if (ammo > 0) {
		EnemyBullet* EnemyBullet = myEnemyBulletPool.GetEnemyBullet();


		EnemyBullet->Initialize(a, b, c);


		ammo -= 1;
	}
}

void EnemyBulletFactory::privRecycleEnemyBullet(GameObject* b)
{
	myEnemyBulletPool.ReturnEnemyBullet(static_cast<EnemyBullet*>(b));
	ammo += 1;
}

void EnemyBulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
