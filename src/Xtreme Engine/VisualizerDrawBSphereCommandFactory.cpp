

#include "VisualizerDrawBSphereCommandFactory.h"
#include "VisualizerDrawBSphereCommandObjectPool.h"
#include "VisualizerDrawBSphereCommand.h"

VisualizerDrawBSphereCommandFactory* VisualizerDrawBSphereCommandFactory::ptrInstance = nullptr;

VisualizerDrawBSphereCommand* VisualizerDrawBSphereCommandFactory::privCreateVisualizerDrawBSphereCommand(Matrix a, Vect b)
{
	
		VisualizerDrawBSphereCommand* VisualizerDrawBSphereCommand = myVisualizerDrawBSphereCommandPool.GetVisualizerDrawBSphereCommand();


		VisualizerDrawBSphereCommand->Initialize(a, b);

		return VisualizerDrawBSphereCommand;
}

void VisualizerDrawBSphereCommandFactory::privRecycleVisualizerDrawBSphereCommand(VisualizerDrawBSphereCommand* b)
{
	myVisualizerDrawBSphereCommandPool.ReturnVisualizerDrawBSphereCommand(static_cast<VisualizerDrawBSphereCommand*>(b));
}

void VisualizerDrawBSphereCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
