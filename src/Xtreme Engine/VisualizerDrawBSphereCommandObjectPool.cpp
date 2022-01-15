#include "VisualizerDrawBSphereCommandObjectPool.h"
#include "VisualizerDrawBSphereCommand.h"

VisualizerDrawBSphereCommandObjectPool::VisualizerDrawBSphereCommandObjectPool()
{
}

VisualizerDrawBSphereCommandObjectPool::~VisualizerDrawBSphereCommandObjectPool()
{
	while (!recycledItems.empty())
	{
		//

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active VisualizerDrawBSphereCommands out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

VisualizerDrawBSphereCommand* VisualizerDrawBSphereCommandObjectPool::GetVisualizerDrawBSphereCommand()
{
	VisualizerDrawBSphereCommand* b;

	if (recycledItems.empty())
	{

		b = new VisualizerDrawBSphereCommand();
		activeItems.push_back(static_cast<VisualizerDrawBSphereCommand*>(b));
		//DebugMsg::out("VisualizerDrawBSphereCommand newed!\n");

	}
	else
	{
		//DebugMsg::out("VisualizerDrawBSphereCommand reused!\n");

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<VisualizerDrawBSphereCommand*>(b));


	}
	//DebugMsg::out("VisualizerDrawBSphereCommand get!\n");
	return b;


}

void VisualizerDrawBSphereCommandObjectPool::ReturnVisualizerDrawBSphereCommand(VisualizerDrawBSphereCommand* b)
{
	activeItems.remove(static_cast<VisualizerDrawBSphereCommand*>(b));
	recycledItems.push(static_cast<VisualizerDrawBSphereCommand*>(b));
	//DebugMsg::out("VisualizerDrawBSphereCommand recycled!\n");


}