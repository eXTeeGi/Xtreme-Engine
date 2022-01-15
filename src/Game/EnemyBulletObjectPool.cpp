#include "EnemyBulletObjectPool.h"
#include "EnemyBullet.h"

EnemyBulletObjectPool::EnemyBulletObjectPool()
{
}

EnemyBulletObjectPool::~EnemyBulletObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("EnemyBullets out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active EnemyBullets out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

EnemyBullet* EnemyBulletObjectPool::GetEnemyBullet()
{
	EnemyBullet* b;

	if (recycledItems.empty())
	{

		b = new EnemyBullet();
		activeItems.push_back(static_cast<EnemyBullet*>(b));
		//DebugMsg::out("EnemyBullet newed!\n");

	}
	else
	{
		//DebugMsg::out("EnemyBullet reused!\n");

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<EnemyBullet*>(b));


	}
	//DebugMsg::out("EnemyBullet get!\n");
	return b;


}

void EnemyBulletObjectPool::ReturnEnemyBullet(EnemyBullet* b)
{
	activeItems.remove(static_cast<EnemyBullet*>(b));
	recycledItems.push(static_cast<EnemyBullet*>(b));
	//DebugMsg::out("EnemyBullet recycled!\n");


}