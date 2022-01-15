

#include "PowerupFactory.h"
#include "PowerupObjectPool.h"
#include "Powerup.h"

PowerupFactory* PowerupFactory::ptrInstance = nullptr;

Powerup* PowerupFactory::privCreatePowerup(Vect a)
{
	Powerup* Powerup = nullptr;

	if (ammo > 0) {
		Powerup = myPowerupPool.GetPowerup();


		Powerup->Initialize(a);


		ammo -= 1;
	}

	return Powerup;
}

void PowerupFactory::privRecyclePowerup(GameObject* b)
{
	myPowerupPool.ReturnPowerup(static_cast<Powerup*>(b));
	ammo += 1;
}

void PowerupFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
