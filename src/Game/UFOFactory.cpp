

#include "UFOFactory.h"
#include "UFOObjectPool.h"
#include "UFO.h"

UFOFactory* UFOFactory::ptrInstance = nullptr;

UFO* UFOFactory::privCreateUFO(Vect a)
{
	UFO* UFO = nullptr;

	if (ammo > 0) {
		UFO = myUFOPool.GetUFO();


		UFO->Initialize(a);


		ammo -= 1;
	}

	return UFO;
}

void UFOFactory::privRecycleUFO(GameObject* b)
{
	myUFOPool.ReturnUFO(static_cast<UFO*>(b));
	ammo += 1;
}

void UFOFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
