#include "VisualizerDrawAABBCommandObjectPool.h"
#include "VisualizerDrawAABBCommand.h"

VisualizerDrawAABBCommandObjectPool::VisualizerDrawAABBCommandObjectPool()
{
}

VisualizerDrawAABBCommandObjectPool::~VisualizerDrawAABBCommandObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("VisualizerDrawAABBCommands out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active VisualizerDrawAABBCommands out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

VisualizerDrawAABBCommand* VisualizerDrawAABBCommandObjectPool::GetVisualizerDrawAABBCommand()
{
	VisualizerDrawAABBCommand* b;

	if (recycledItems.empty())
	{

		b = new VisualizerDrawAABBCommand();
		activeItems.push_back(static_cast<VisualizerDrawAABBCommand*>(b));
		//DebugMsg::out("VisualizerDrawAABBCommand newed!\n");

	}
	else
	{
		//DebugMsg::out("VisualizerDrawAABBCommand reused!\n");

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<VisualizerDrawAABBCommand*>(b));


	}
	//DebugMsg::out("VisualizerDrawAABBCommand get!\n");
	return b;


}

void VisualizerDrawAABBCommandObjectPool::ReturnVisualizerDrawAABBCommand(VisualizerDrawAABBCommand* b)
{
	activeItems.remove(static_cast<VisualizerDrawAABBCommand*>(b));
	recycledItems.push(static_cast<VisualizerDrawAABBCommand*>(b));
	//DebugMsg::out("VisualizerDrawAABBCommand recycled!\n");


}