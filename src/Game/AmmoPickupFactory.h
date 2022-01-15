

#ifndef _AmmoPickupFactory
#define _AmmoPickupFactory

#include "AmmoPickupObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class AmmoPickupFactory
{
private:
	AmmoPickupFactory() = default;
	AmmoPickupFactory(const AmmoPickupFactory&) = delete;
	AmmoPickupFactory& operator=(const AmmoPickupFactory&) = delete;
	~AmmoPickupFactory() = default;

	static AmmoPickupFactory* ptrInstance;
	static AmmoPickupFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new AmmoPickupFactory();
		return *ptrInstance;
	};

	AmmoPickupObjectPool myAmmoPickupPool;

	AmmoPickup* privCreateAmmoPickup(Vect);
	void privRecycleAmmoPickup(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static AmmoPickup* CreateAmmoPickup(Vect a) { return Instance().privCreateAmmoPickup(a); };
	static void RecycleAmmoPickup(GameObject* b) { Instance().privRecycleAmmoPickup(b); };
	static void ExitActive() { Instance().myAmmoPickupPool.ExitActive(); }

	static void Terminate();
};


#endif _AmmoPickupFactory