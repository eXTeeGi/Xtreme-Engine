

#ifndef _UFOFactory
#define _UFOFactory

#include "UFOObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class UFOFactory
{
private:
	UFOFactory() = default;
	UFOFactory(const UFOFactory&) = delete;
	UFOFactory& operator=(const UFOFactory&) = delete;
	~UFOFactory() = default;

	static UFOFactory* ptrInstance;
	static UFOFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new UFOFactory();
		return *ptrInstance;
	};

	UFOObjectPool myUFOPool;

	UFO* privCreateUFO(Vect);
	void privRecycleUFO(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static UFO* CreateUFO(Vect a) { return Instance().privCreateUFO(a); };
	static void RecycleUFO(GameObject* b) { Instance().privRecycleUFO(b); };
	static void ExitActive() { Instance().myUFOPool.ExitActive(); }

	static void Terminate();
};


#endif _UFOFactory