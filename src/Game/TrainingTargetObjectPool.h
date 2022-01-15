
#ifndef _TrainingTargetObjectPool
#define _TrainingTargetObjectPool

#include <stack>
#include <list>

class TrainingTarget;

class TrainingTargetObjectPool
{
private:
	std::stack<TrainingTarget*> recycledItems;
	std::list<TrainingTarget*> activeItems;

public:
	TrainingTargetObjectPool();
	TrainingTargetObjectPool(const TrainingTargetObjectPool&) = delete;
	TrainingTargetObjectPool& operator=(const TrainingTargetObjectPool&) = delete;
	~TrainingTargetObjectPool();

	TrainingTarget* GetTarget();
	void ExitActive();

	void ReturnTarget(TrainingTarget* b);
};


#endif _TrainingTargetObjectPool
