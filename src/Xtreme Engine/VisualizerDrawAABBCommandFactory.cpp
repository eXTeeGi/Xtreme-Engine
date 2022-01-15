

#include "VisualizerDrawAABBCommandFactory.h"
#include "VisualizerDrawAABBCommandObjectPool.h"
#include "VisualizerDrawAABBCommand.h"

VisualizerDrawAABBCommandFactory* VisualizerDrawAABBCommandFactory::ptrInstance = nullptr;

VisualizerDrawAABBCommand* VisualizerDrawAABBCommandFactory::privCreateVisualizerDrawAABBCommand(Matrix a, Vect b)
{
	
		VisualizerDrawAABBCommand* VisualizerDrawAABBCommand = myVisualizerDrawAABBCommandPool.GetVisualizerDrawAABBCommand();


		VisualizerDrawAABBCommand->Initialize(a, b);

		return VisualizerDrawAABBCommand;
}

void VisualizerDrawAABBCommandFactory::privRecycleVisualizerDrawAABBCommand(VisualizerDrawAABBCommand* b)
{
	myVisualizerDrawAABBCommandPool.ReturnVisualizerDrawAABBCommand(static_cast<VisualizerDrawAABBCommand*>(b));
}

void VisualizerDrawAABBCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
