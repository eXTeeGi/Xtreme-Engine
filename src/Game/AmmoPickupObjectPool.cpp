#include "AmmoPickupObjectPool.h"
#include "AmmoPickup.h"

#include "WaveController.h"

AmmoPickupObjectPool::AmmoPickupObjectPool()
{
}

AmmoPickupObjectPool::~AmmoPickupObjectPool()
{
	while (!recycledItems.empty())
	{
		//

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active AmmoPickups out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void AmmoPickupObjectPool::ExitActive() {
	std::list<AmmoPickup*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

AmmoPickup* AmmoPickupObjectPool::GetAmmoPickup()
{
	AmmoPickup* b;

	if (recycledItems.empty())
	{

		b = new AmmoPickup();
		activeItems.push_back(static_cast<AmmoPickup*>(b));
		//DebugMsg::out("AmmoPickup newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<AmmoPickup*>(b));


	}
	//DebugMsg::out("AmmoPickup get!\n");
	return b;


}

void AmmoPickupObjectPool::ReturnAmmoPickup(AmmoPickup* b)
{
	activeItems.remove(static_cast<AmmoPickup*>(b));
	recycledItems.push(static_cast<AmmoPickup*>(b));
	//DebugMsg::out("AmmoPickup recycled!\n");

	if (activeItems.empty()) WaveController::tanksGone();
}