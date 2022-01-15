#include "BulletObjectPool.h"
#include "Bullet.h"

BulletObjectPool::BulletObjectPool()
{
}

BulletObjectPool::~BulletObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("Bullets out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active bullets out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

Bullet* BulletObjectPool::GetBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{

		b = new Bullet();
		activeItems.push_back(static_cast<Bullet*>(b));
		//DebugMsg::out("Bullet newed!\n");

	}
	else
	{
		//DebugMsg::out("Bullet reused!\n");

		b = recycledItems.top();
		recycledItems.pop();	
		activeItems.push_back(static_cast<Bullet*>(b));


	}
	//DebugMsg::out("Bullet get!\n");
	return b;

	
}

void BulletObjectPool::ReturnBullet(Bullet* b)
{
	activeItems.remove(static_cast<Bullet*>(b));
	recycledItems.push(static_cast<Bullet*>(b));
	//DebugMsg::out("Bullet recycled!\n");


}