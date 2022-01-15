#include "TrainingTargetObjectPool.h"
#include "TrainingTarget.h"

#include "WaveController.h"

TrainingTargetObjectPool::TrainingTargetObjectPool()
{
}

TrainingTargetObjectPool::~TrainingTargetObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("Targets out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active Targets out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void TrainingTargetObjectPool::ExitActive() {
	std::list<TrainingTarget*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

TrainingTarget* TrainingTargetObjectPool::GetTarget()
{
	TrainingTarget* b;

	if (recycledItems.empty())
	{

		b = new TrainingTarget(Vect(0, 0, 0));
		activeItems.push_back(static_cast<TrainingTarget*>(b));
		//DebugMsg::out("TrainingTarget newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<TrainingTarget*>(b));


	}
	//DebugMsg::out("TrainingTarget get!\n");
	return b;


}

void TrainingTargetObjectPool::ReturnTarget(TrainingTarget* b)
{
	activeItems.remove(static_cast<TrainingTarget*>(b));
	recycledItems.push(static_cast<TrainingTarget*>(b));
	//DebugMsg::out("TrainingTarget recycled!\n");

	if (activeItems.empty()) WaveController::targetsGone();
}