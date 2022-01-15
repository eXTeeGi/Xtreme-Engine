

#ifndef _VisualizerDrawAABBCommandFactory
#define _VisualizerDrawAABBCommandFactory

#include "VisualizerDrawAABBCommandObjectPool.h"
#include "Matrix.h"
class Matrix;
class Vect;

class VisualizerDrawAABBCommandFactory
{
private:
	VisualizerDrawAABBCommandFactory() = default;
	VisualizerDrawAABBCommandFactory(const VisualizerDrawAABBCommandFactory&) = delete;
	VisualizerDrawAABBCommandFactory& operator=(const VisualizerDrawAABBCommandFactory&) = delete;
	~VisualizerDrawAABBCommandFactory() = default;

	static VisualizerDrawAABBCommandFactory* ptrInstance;
	static VisualizerDrawAABBCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new VisualizerDrawAABBCommandFactory();
		return *ptrInstance;
	};

	VisualizerDrawAABBCommandObjectPool myVisualizerDrawAABBCommandPool;

	VisualizerDrawAABBCommand* privCreateVisualizerDrawAABBCommand(Matrix, Vect);
	void privRecycleVisualizerDrawAABBCommand(VisualizerDrawAABBCommand* b);

public:

	static VisualizerDrawAABBCommand* CreateVisualizerDrawAABBCommand(Matrix a, Vect b) { return Instance().privCreateVisualizerDrawAABBCommand(a, b); };
	static void RecycleVisualizerDrawAABBCommand(VisualizerDrawAABBCommand* b) { Instance().privRecycleVisualizerDrawAABBCommand(b); };

	static void Terminate();
};


#endif _VisualizerDrawAABBCommandFactory