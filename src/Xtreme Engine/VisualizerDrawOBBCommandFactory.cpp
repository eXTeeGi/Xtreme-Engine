

#include "VisualizerDrawOBBCommandFactory.h"
#include "VisualizerDrawOBBCommandObjectPool.h"
#include "VisualizerDrawOBBCommand.h"

VisualizerDrawOBBCommandFactory* VisualizerDrawOBBCommandFactory::ptrInstance = nullptr;

VisualizerDrawOBBCommand* VisualizerDrawOBBCommandFactory::privCreateVisualizerDrawOBBCommand(Matrix a, Vect b)
{

	VisualizerDrawOBBCommand* VisualizerDrawOBBCommand = myVisualizerDrawOBBCommandPool.GetVisualizerDrawOBBCommand();


	VisualizerDrawOBBCommand->Initialize(a, b);

	return VisualizerDrawOBBCommand;
}

void VisualizerDrawOBBCommandFactory::privRecycleVisualizerDrawOBBCommand(VisualizerDrawOBBCommand* b)
{
	myVisualizerDrawOBBCommandPool.ReturnVisualizerDrawOBBCommand(static_cast<VisualizerDrawOBBCommand*>(b));
}

void VisualizerDrawOBBCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
