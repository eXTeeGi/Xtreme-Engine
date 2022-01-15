

#include "AmmoPickupFactory.h"
#include "AmmoPickupObjectPool.h"
#include "AmmoPickup.h"

AmmoPickupFactory* AmmoPickupFactory::ptrInstance = nullptr;

AmmoPickup* AmmoPickupFactory::privCreateAmmoPickup(Vect a)
{
	AmmoPickup* AmmoPickup = nullptr;

	if (ammo > 0) {
		AmmoPickup = myAmmoPickupPool.GetAmmoPickup();


		AmmoPickup->Initialize(a);


		ammo -= 1;
	}

	return AmmoPickup;
}

void AmmoPickupFactory::privRecycleAmmoPickup(GameObject* b)
{
	myAmmoPickupPool.ReturnAmmoPickup(static_cast<AmmoPickup*>(b));
	ammo += 1;
}

void AmmoPickupFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
