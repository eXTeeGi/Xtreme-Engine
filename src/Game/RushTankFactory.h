

#ifndef _RushTankFactory
#define _RushTankFactory

#include "RushTankObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class RushTankFactory
{
private:
	RushTankFactory() = default;
	RushTankFactory(const RushTankFactory&) = delete;
	RushTankFactory& operator=(const RushTankFactory&) = delete;
	~RushTankFactory() = default;

	static RushTankFactory* ptrInstance;
	static RushTankFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new RushTankFactory();
		return *ptrInstance;
	};

	RushTankObjectPool myRushTankPool;

	RushTank* privCreateRushTank(Vect);
	void privRecycleRushTank(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static RushTank* CreateRushTank(Vect a) { return Instance().privCreateRushTank(a); };
	static void RecycleRushTank(GameObject* b) { Instance().privRecycleRushTank(b); };
	static void ExitActive() { Instance().myRushTankPool.ExitActive(); }

	static void Terminate();
};


#endif _RushTankFactory