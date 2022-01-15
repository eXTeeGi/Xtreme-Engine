

#include "PlayerBulletFactory.h"
#include "PlayerBulletObjectPool.h"
#include "PlayerBullet.h"

PlayerBulletFactory* PlayerBulletFactory::ptrInstance = nullptr;

void PlayerBulletFactory::privCreatePlayerBullet(Matrix a, Matrix b, Vect c)
{
	if (ammo > 0) {
		PlayerBullet* PlayerBullet = myPlayerBulletPool.GetPlayerBullet();


		PlayerBullet->Initialize(a, b, c);


		ammo -= 1;
	}
}

void PlayerBulletFactory::privRecyclePlayerBullet(GameObject* b)
{
	myPlayerBulletPool.ReturnPlayerBullet(static_cast<PlayerBullet*>(b));
	ammo += 1;
}

void PlayerBulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
