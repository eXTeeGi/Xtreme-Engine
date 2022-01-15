
#ifndef _PowerupObjectPool
#define _PowerupObjectPool

#include <stack>
#include <list>

class Powerup;

class PowerupObjectPool
{
private:
	std::stack<Powerup*> recycledItems;
	std::list<Powerup*> activeItems;

public:
	PowerupObjectPool();
	PowerupObjectPool(const PowerupObjectPool&) = delete;
	PowerupObjectPool& operator=(const PowerupObjectPool&) = delete;
	~PowerupObjectPool();

	Powerup* GetPowerup();
	void ExitActive();

	void ReturnPowerup(Powerup* b);
};


#endif _PowerupObjectPool
