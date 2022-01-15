

#include "EnemyTankFactory.h"
#include "EnemyTankObjectPool.h"
#include "EnemyTank.h"

EnemyTankFactory* EnemyTankFactory::ptrInstance = nullptr;

EnemyTank* EnemyTankFactory::privCreateEnemyTank(Vect a)
{
	EnemyTank* EnemyTank = nullptr;

	if (ammo > 0) {
		EnemyTank = myEnemyTankPool.GetEnemyTank();


		EnemyTank->Initialize(a);

		
		ammo -= 1;
	}

	return EnemyTank;
}

void EnemyTankFactory::privRecycleEnemyTank(GameObject* b)
{
	myEnemyTankPool.ReturnEnemyTank(static_cast<EnemyTank*>(b));
	ammo += 1;
}

void EnemyTankFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
