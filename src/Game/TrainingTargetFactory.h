

#ifndef _TrainingTargetFactory
#define _TrainingTargetFactory

#include "TrainingTargetObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class TrainingTargetFactory
{
private:
	TrainingTargetFactory() = default;
	TrainingTargetFactory(const TrainingTargetFactory&) = delete;
	TrainingTargetFactory& operator=(const TrainingTargetFactory&) = delete;
	~TrainingTargetFactory() = default;

	static TrainingTargetFactory* ptrInstance;
	static TrainingTargetFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TrainingTargetFactory();
		return *ptrInstance;
	};

	TrainingTargetObjectPool myTargetPool;

	TrainingTarget* privCreateTarget(Vect);
	void privRecycleTarget(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;


public:

	static TrainingTarget* CreateTarget(Vect a) { return Instance().privCreateTarget(a); };
	static void RecycleTarget(GameObject* b) { Instance().privRecycleTarget(b); };
	static void ExitActive() { Instance().myTargetPool.ExitActive(); }

	static void Terminate();
};


#endif _TrainingTargetFactory