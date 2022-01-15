
#ifndef _VisualizerDrawAABBCommandObjectPool
#define _VisualizerDrawAABBCommandObjectPool

#include <stack>
#include <list>

class VisualizerDrawAABBCommand;

class VisualizerDrawAABBCommandObjectPool
{
private:
	std::stack<VisualizerDrawAABBCommand*> recycledItems;
	std::list<VisualizerDrawAABBCommand*> activeItems;

public:
	VisualizerDrawAABBCommandObjectPool();
	VisualizerDrawAABBCommandObjectPool(const VisualizerDrawAABBCommandObjectPool&) = delete;
	VisualizerDrawAABBCommandObjectPool& operator=(const VisualizerDrawAABBCommandObjectPool&) = delete;
	~VisualizerDrawAABBCommandObjectPool();

	VisualizerDrawAABBCommand* GetVisualizerDrawAABBCommand();

	void ReturnVisualizerDrawAABBCommand(VisualizerDrawAABBCommand* b);
};


#endif _VisualizerDrawAABBCommandObjectPool
