
#ifndef _VisualizerDrawOBBCommandObjectPool
#define _VisualizerDrawOBBCommandObjectPool

#include <stack>
#include <list>

class VisualizerDrawOBBCommand;

class VisualizerDrawOBBCommandObjectPool
{
private:
	std::stack<VisualizerDrawOBBCommand*> recycledItems;
	std::list<VisualizerDrawOBBCommand*> activeItems;

public:
	VisualizerDrawOBBCommandObjectPool();
	VisualizerDrawOBBCommandObjectPool(const VisualizerDrawOBBCommandObjectPool&) = delete;
	VisualizerDrawOBBCommandObjectPool& operator=(const VisualizerDrawOBBCommandObjectPool&) = delete;
	~VisualizerDrawOBBCommandObjectPool();

	VisualizerDrawOBBCommand* GetVisualizerDrawOBBCommand();

	void ReturnVisualizerDrawOBBCommand(VisualizerDrawOBBCommand* b);
};


#endif _VisualizerDrawOBBCommandObjectPool
