
#ifndef _AmmoPickupObjectPool
#define _AmmoPickupObjectPool

#include <stack>
#include <list>

class AmmoPickup;

class AmmoPickupObjectPool
{
private:
	std::stack<AmmoPickup*> recycledItems;
	std::list<AmmoPickup*> activeItems;

public:
	AmmoPickupObjectPool();
	AmmoPickupObjectPool(const AmmoPickupObjectPool&) = delete;
	AmmoPickupObjectPool& operator=(const AmmoPickupObjectPool&) = delete;
	~AmmoPickupObjectPool();

	AmmoPickup* GetAmmoPickup();
	void ExitActive();

	void ReturnAmmoPickup(AmmoPickup* b);
};


#endif _AmmoPickupObjectPool
