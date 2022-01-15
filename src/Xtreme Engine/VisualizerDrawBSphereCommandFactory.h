

#ifndef _VisualizerDrawBSphereCommandFactory
#define _VisualizerDrawBSphereCommandFactory

#include "VisualizerDrawBSphereCommandObjectPool.h"
#include "Matrix.h"
class Matrix;
class Vect;

class VisualizerDrawBSphereCommandFactory
{
private:
	VisualizerDrawBSphereCommandFactory() = default;
	VisualizerDrawBSphereCommandFactory(const VisualizerDrawBSphereCommandFactory&) = delete;
	VisualizerDrawBSphereCommandFactory& operator=(const VisualizerDrawBSphereCommandFactory&) = delete;
	~VisualizerDrawBSphereCommandFactory() = default;

	static VisualizerDrawBSphereCommandFactory* ptrInstance;
	static VisualizerDrawBSphereCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new VisualizerDrawBSphereCommandFactory();
		return *ptrInstance;
	};

	VisualizerDrawBSphereCommandObjectPool myVisualizerDrawBSphereCommandPool;

	VisualizerDrawBSphereCommand* privCreateVisualizerDrawBSphereCommand(Matrix, Vect);
	void privRecycleVisualizerDrawBSphereCommand(VisualizerDrawBSphereCommand* b);

public:

	static VisualizerDrawBSphereCommand* CreateVisualizerDrawBSphereCommand(Matrix a, Vect b) { return Instance().privCreateVisualizerDrawBSphereCommand(a, b); };
	static void RecycleVisualizerDrawBSphereCommand(VisualizerDrawBSphereCommand* b) { Instance().privRecycleVisualizerDrawBSphereCommand(b); };

	static void Terminate();
};


#endif _VisualizerDrawBSphereCommandFactory