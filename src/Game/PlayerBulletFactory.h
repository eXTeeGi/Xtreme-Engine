

#ifndef _PlayerBulletFactory
#define _PlayerBulletFactory

#include "PlayerBulletObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class PlayerBulletFactory
{
private:
	PlayerBulletFactory() = default;
	PlayerBulletFactory(const PlayerBulletFactory&) = delete;
	PlayerBulletFactory& operator=(const PlayerBulletFactory&) = delete;
	~PlayerBulletFactory() = default;

	static PlayerBulletFactory* ptrInstance;
	static PlayerBulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerBulletFactory();
		return *ptrInstance;
	};

	PlayerBulletObjectPool myPlayerBulletPool;

	void privCreatePlayerBullet(Matrix, Matrix, Vect);
	void privRecyclePlayerBullet(GameObject* b);

	int maxAmmo = 99;
	int ammo = maxAmmo;

public:

	static void CreatePlayerBullet(Matrix a, Matrix b, Vect c) { Instance().privCreatePlayerBullet(a, b, c); };
	static void RecyclePlayerBullet(GameObject* b) { Instance().privRecyclePlayerBullet(b); };

	static void Terminate();
};


#endif _PlayerBulletFactory