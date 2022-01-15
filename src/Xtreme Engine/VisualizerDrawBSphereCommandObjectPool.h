
#ifndef _VisualizerDrawBSphereCommandObjectPool
#define _VisualizerDrawBSphereCommandObjectPool

#include <stack>
#include <list>

class VisualizerDrawBSphereCommand;

class VisualizerDrawBSphereCommandObjectPool
{
private:
	std::stack<VisualizerDrawBSphereCommand*> recycledItems;
	std::list<VisualizerDrawBSphereCommand*> activeItems;

public:
	VisualizerDrawBSphereCommandObjectPool();
	VisualizerDrawBSphereCommandObjectPool(const VisualizerDrawBSphereCommandObjectPool&) = delete;
	VisualizerDrawBSphereCommandObjectPool& operator=(const VisualizerDrawBSphereCommandObjectPool&) = delete;
	~VisualizerDrawBSphereCommandObjectPool();

	VisualizerDrawBSphereCommand* GetVisualizerDrawBSphereCommand();

	void ReturnVisualizerDrawBSphereCommand(VisualizerDrawBSphereCommand* b);
};


#endif _VisualizerDrawBSphereCommandObjectPool
