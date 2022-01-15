

#ifndef _EnemyTankFactory
#define _EnemyTankFactory

#include "EnemyTankObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class EnemyTankFactory
{
private:
	EnemyTankFactory() = default;
	EnemyTankFactory(const EnemyTankFactory&) = delete;
	EnemyTankFactory& operator=(const EnemyTankFactory&) = delete;
	~EnemyTankFactory() = default;

	static EnemyTankFactory* ptrInstance;
	static EnemyTankFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyTankFactory();
		return *ptrInstance;
	};

	EnemyTankObjectPool myEnemyTankPool;

	EnemyTank* privCreateEnemyTank(Vect);
	void privRecycleEnemyTank(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static EnemyTank* CreateEnemyTank(Vect a) { return Instance().privCreateEnemyTank(a); };
	static void RecycleEnemyTank(GameObject* b) { Instance().privRecycleEnemyTank(b); };
	static void ExitActive() { Instance().myEnemyTankPool.ExitActive(); }

	static void Terminate();
};


#endif _EnemyTankFactory