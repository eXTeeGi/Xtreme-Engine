#include "UFOObjectPool.h"
#include "UFO.h"

#include "WaveController.h"

UFOObjectPool::UFOObjectPool()
{
}

UFOObjectPool::~UFOObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("UFOs out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active UFOs out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

void UFOObjectPool::ExitActive() {
	std::list<UFO*>::iterator it;
	for (it = activeItems.begin(); it != activeItems.end(); it++) {
		(*it)->SubmitExit();
	}
}

UFO* UFOObjectPool::GetUFO()
{
	UFO* b;

	if (recycledItems.empty())
	{

		b = new UFO(Vect(0, 0, 0));
		activeItems.push_back(static_cast<UFO*>(b));
		//DebugMsg::out("UFO newed!\n");

	}
	else
	{

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<UFO*>(b));


	}
	//DebugMsg::out("UFO get!\n");
	return b;


}

void UFOObjectPool::ReturnUFO(UFO* b)
{
	activeItems.remove(static_cast<UFO*>(b));
	recycledItems.push(static_cast<UFO*>(b));
	//DebugMsg::out("UFO recycled!\n");

	if (activeItems.empty()) WaveController::UFOsGone();
}