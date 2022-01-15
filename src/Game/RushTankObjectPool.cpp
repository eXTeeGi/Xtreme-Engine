#include "RushTankObjectPool.h"
#include "RushTank.h"

#include "WaveController.h"

RushTankObjectPool::RushTankObjectPool()
{
}

RushTankObjectPool::~RushTankObjectPool()
{
	while (!recycledItems.empty())
	{
		//

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active RushTanks out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void RushTankObjectPool::ExitActive() {
	std::list<RushTank*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

RushTank* RushTankObjectPool::GetRushTank()
{
	RushTank* b;

	if (recycledItems.empty())
	{

		b = new RushTank(Vect(0, 0, 0));
		activeItems.push_back(static_cast<RushTank*>(b));
		//DebugMsg::out("RushTank newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<RushTank*>(b));


	}
	//DebugMsg::out("RushTank get!\n");
	return b;


}

void RushTankObjectPool::ReturnRushTank(RushTank* b)
{
	activeItems.remove(static_cast<RushTank*>(b));
	recycledItems.push(static_cast<RushTank*>(b));
	//DebugMsg::out("RushTank recycled!\n");

	if (activeItems.empty()) WaveController::rushTanksGone();
}