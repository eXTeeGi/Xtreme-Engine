
#ifndef _RushTankObjectPool
#define _RushTankObjectPool

#include <stack>
#include <list>

class RushTank;

class RushTankObjectPool
{
private:
	std::stack<RushTank*> recycledItems;
	std::list<RushTank*> activeItems;

public:
	RushTankObjectPool();
	RushTankObjectPool(const RushTankObjectPool&) = delete;
	RushTankObjectPool& operator=(const RushTankObjectPool&) = delete;
	~RushTankObjectPool();

	RushTank* GetRushTank();
	void ExitActive();

	void ReturnRushTank(RushTank* b);
};


#endif _RushTankObjectPool
