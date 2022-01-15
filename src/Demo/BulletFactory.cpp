

#include "BulletFactory.h"
#include "BulletObjectPool.h"
#include "Bullet.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;

void BulletFactory::privCreateBullet(Matrix a, Matrix b, Vect c)
{
	if (ammo > 0) {
		Bullet* bullet = myBulletPool.GetBullet();


		bullet->Initialize(a,b,c);


		ammo -= 1;
	}
}

void BulletFactory::privRecycleBullet(GameObject* b)
{
	myBulletPool.ReturnBullet(static_cast<Bullet*>(b));
	ammo += 1;
}

void BulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;	
}
