

#include "RushTankFactory.h"
#include "RushTankObjectPool.h"
#include "RushTank.h"

RushTankFactory* RushTankFactory::ptrInstance = nullptr;

RushTank* RushTankFactory::privCreateRushTank(Vect a)
{
	RushTank* RushTank = nullptr;

	if (ammo > 0) {
		RushTank = myRushTankPool.GetRushTank();


		RushTank->Initialize(a);


		ammo -= 1;
	}

	return RushTank;
}

void RushTankFactory::privRecycleRushTank(GameObject* b)
{
	myRushTankPool.ReturnRushTank(static_cast<RushTank*>(b));
	ammo += 1;
}

void RushTankFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
