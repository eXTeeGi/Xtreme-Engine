
#ifndef _EnemyBulletObjectPool
#define _EnemyBulletObjectPool

#include <stack>
#include <list>

class EnemyBullet;

class EnemyBulletObjectPool
{
private:
	std::stack<EnemyBullet*> recycledItems;
	std::list<EnemyBullet*> activeItems;

public:
	EnemyBulletObjectPool();
	EnemyBulletObjectPool(const EnemyBulletObjectPool&) = delete;
	EnemyBulletObjectPool& operator=(const EnemyBulletObjectPool&) = delete;
	~EnemyBulletObjectPool();

	EnemyBullet* GetEnemyBullet();

	void ReturnEnemyBullet(EnemyBullet* b);
};


#endif _EnemyBulletObjectPool
