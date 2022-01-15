#include "EnemyTankObjectPool.h"
#include "EnemyTank.h"

#include "WaveController.h"

EnemyTankObjectPool::EnemyTankObjectPool()
{
}

EnemyTankObjectPool::~EnemyTankObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("EnemyTanks out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active EnemyTanks out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void EnemyTankObjectPool::ExitActive() {
	std::list<EnemyTank*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

EnemyTank* EnemyTankObjectPool::GetEnemyTank()
{
	EnemyTank* b;

	if (recycledItems.empty())
	{

		b = new EnemyTank(Vect(0,0,0));
		activeItems.push_back(static_cast<EnemyTank*>(b));
		//DebugMsg::out("EnemyTank newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<EnemyTank*>(b));


	}
	//DebugMsg::out("EnemyTank get!\n");
	return b;


}

void EnemyTankObjectPool::ReturnEnemyTank(EnemyTank* b)
{
	activeItems.remove(static_cast<EnemyTank*>(b));
	recycledItems.push(static_cast<EnemyTank*>(b));
	//DebugMsg::out("EnemyTank recycled!\n");

	if (activeItems.empty()) WaveController::tanksGone();
}