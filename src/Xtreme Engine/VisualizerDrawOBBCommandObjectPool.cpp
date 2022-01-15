#include "VisualizerDrawOBBCommandObjectPool.h"
#include "VisualizerDrawOBBCommand.h"

VisualizerDrawOBBCommandObjectPool::VisualizerDrawOBBCommandObjectPool()
{
}

VisualizerDrawOBBCommandObjectPool::~VisualizerDrawOBBCommandObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("VisualizerDrawOBBCommands out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active VisualizerDrawOBBCommands out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

VisualizerDrawOBBCommand* VisualizerDrawOBBCommandObjectPool::GetVisualizerDrawOBBCommand()
{
	VisualizerDrawOBBCommand* b;

	if (recycledItems.empty())
	{

		b = new VisualizerDrawOBBCommand();
		activeItems.push_back(static_cast<VisualizerDrawOBBCommand*>(b));
		//DebugMsg::out("VisualizerDrawOBBCommand newed!\n");

	}
	else
	{
		//DebugMsg::out("VisualizerDrawOBBCommand reused!\n");

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<VisualizerDrawOBBCommand*>(b));


	}
	//DebugMsg::out("VisualizerDrawOBBCommand get!\n");
	return b;


}

void VisualizerDrawOBBCommandObjectPool::ReturnVisualizerDrawOBBCommand(VisualizerDrawOBBCommand* b)
{
	activeItems.remove(static_cast<VisualizerDrawOBBCommand*>(b));
	recycledItems.push(static_cast<VisualizerDrawOBBCommand*>(b));
	//DebugMsg::out("VisualizerDrawOBBCommand recycled!\n");


}