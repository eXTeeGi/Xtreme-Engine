
#ifndef _EnemyTankObjectPool
#define _EnemyTankObjectPool

#include <stack>
#include <list>

class EnemyTank;

class EnemyTankObjectPool
{
private:
	std::stack<EnemyTank*> recycledItems;
	std::list<EnemyTank*> activeItems;

public:
	EnemyTankObjectPool();
	EnemyTankObjectPool(const EnemyTankObjectPool&) = delete;
	EnemyTankObjectPool& operator=(const EnemyTankObjectPool&) = delete;
	~EnemyTankObjectPool();

	EnemyTank* GetEnemyTank();
	void ExitActive();

	void ReturnEnemyTank(EnemyTank* b);
};


#endif _EnemyTankObjectPool
