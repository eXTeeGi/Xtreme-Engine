#include "PowerupObjectPool.h"
#include "Powerup.h"

#include "WaveController.h"

PowerupObjectPool::PowerupObjectPool()
{
}

PowerupObjectPool::~PowerupObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("Powerups out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active Powerups out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void PowerupObjectPool::ExitActive() {
	std::list<Powerup*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

Powerup* PowerupObjectPool::GetPowerup()
{
	Powerup* b;

	if (recycledItems.empty())
	{

		b = new Powerup();
		activeItems.push_back(static_cast<Powerup*>(b));
		//DebugMsg::out("Powerup newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<Powerup*>(b));


	}
	//DebugMsg::out("Powerup get!\n");
	return b;


}

void PowerupObjectPool::ReturnPowerup(Powerup* b)
{
	activeItems.remove(static_cast<Powerup*>(b));
	recycledItems.push(static_cast<Powerup*>(b));
	//DebugMsg::out("Powerup recycled!\n");

	if (activeItems.empty()) WaveController::tanksGone();
}