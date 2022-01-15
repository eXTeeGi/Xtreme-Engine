#include "PlayerBulletObjectPool.h"
#include "PlayerBullet.h"

PlayerBulletObjectPool::PlayerBulletObjectPool()
{
}

PlayerBulletObjectPool::~PlayerBulletObjectPool()
{
	while (!recycledItems.empty())
	{
		//DebugMsg::out("PlayerBullets out!\n");

		delete recycledItems.top();
		recycledItems.pop();
	}

	while (!activeItems.empty())
	{
		//DebugMsg::out("Active PlayerBullets out!\n");

		delete activeItems.front();
		activeItems.pop_front();
	}
}

PlayerBullet* PlayerBulletObjectPool::GetPlayerBullet()
{
	PlayerBullet* b;

	if (recycledItems.empty())
	{

		b = new PlayerBullet();
		activeItems.push_back(static_cast<PlayerBullet*>(b));
		//DebugMsg::out("PlayerBullet newed!\n");

	}
	else
	{
		//DebugMsg::out("PlayerBullet reused!\n");

		b = recycledItems.top();
		recycledItems.pop();
		activeItems.push_back(static_cast<PlayerBullet*>(b));


	}
	//DebugMsg::out("PlayerBullet get!\n");
	return b;


}

void PlayerBulletObjectPool::ReturnPlayerBullet(PlayerBullet* b)
{
	activeItems.remove(static_cast<PlayerBullet*>(b));
	recycledItems.push(static_cast<PlayerBullet*>(b));
	//DebugMsg::out("PlayerBullet recycled!\n");


}