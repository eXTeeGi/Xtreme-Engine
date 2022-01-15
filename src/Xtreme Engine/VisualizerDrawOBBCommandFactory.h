

#ifndef _VisualizerDrawOBBCommandFactory
#define _VisualizerDrawOBBCommandFactory

#include "VisualizerDrawOBBCommandObjectPool.h"
#include "Matrix.h"
class Matrix;
class Vect;

class VisualizerDrawOBBCommandFactory
{
private:
	VisualizerDrawOBBCommandFactory() = default;
	VisualizerDrawOBBCommandFactory(const VisualizerDrawOBBCommandFactory&) = delete;
	VisualizerDrawOBBCommandFactory& operator=(const VisualizerDrawOBBCommandFactory&) = delete;
	~VisualizerDrawOBBCommandFactory() = default;

	static VisualizerDrawOBBCommandFactory* ptrInstance;
	static VisualizerDrawOBBCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new VisualizerDrawOBBCommandFactory();
		return *ptrInstance;
	};

	VisualizerDrawOBBCommandObjectPool myVisualizerDrawOBBCommandPool;

	VisualizerDrawOBBCommand* privCreateVisualizerDrawOBBCommand(Matrix, Vect);
	void privRecycleVisualizerDrawOBBCommand(VisualizerDrawOBBCommand* b);

public:

	static VisualizerDrawOBBCommand* CreateVisualizerDrawOBBCommand(Matrix a, Vect b) { return Instance().privCreateVisualizerDrawOBBCommand(a, b); };
	static void RecycleVisualizerDrawOBBCommand(VisualizerDrawOBBCommand* b) { Instance().privRecycleVisualizerDrawOBBCommand(b); };

	static void Terminate();
};


#endif _VisualizerDrawOBBCommandFactory