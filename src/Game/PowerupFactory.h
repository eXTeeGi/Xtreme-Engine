

#ifndef _PowerupFactory
#define _PowerupFactory

#include "PowerupObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class PowerupFactory
{
private:
	PowerupFactory() = default;
	PowerupFactory(const PowerupFactory&) = delete;
	PowerupFactory& operator=(const PowerupFactory&) = delete;
	~PowerupFactory() = default;

	static PowerupFactory* ptrInstance;
	static PowerupFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PowerupFactory();
		return *ptrInstance;
	};

	PowerupObjectPool myPowerupPool;

	Powerup* privCreatePowerup(Vect);
	void privRecyclePowerup(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static Powerup* CreatePowerup(Vect a) { return Instance().privCreatePowerup(a); };
	static void RecyclePowerup(GameObject* b) { Instance().privRecyclePowerup(b); };
	static void ExitActive() { Instance().myPowerupPool.ExitActive(); }

	static void Terminate();
};


#endif _PowerupFactory