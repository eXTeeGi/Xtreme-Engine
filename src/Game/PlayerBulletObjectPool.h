
#ifndef _PlayerBulletObjectPool
#define _PlayerBulletObjectPool

#include <stack>
#include <list>

class PlayerBullet;

class PlayerBulletObjectPool
{
private:
	std::stack<PlayerBullet*> recycledItems;
	std::list<PlayerBullet*> activeItems;

public:
	PlayerBulletObjectPool();
	PlayerBulletObjectPool(const PlayerBulletObjectPool&) = delete;
	PlayerBulletObjectPool& operator=(const PlayerBulletObjectPool&) = delete;
	~PlayerBulletObjectPool();

	PlayerBullet* GetPlayerBullet();

	void ReturnPlayerBullet(PlayerBullet* b);
};


#endif _PlayerBulletObjectPool
