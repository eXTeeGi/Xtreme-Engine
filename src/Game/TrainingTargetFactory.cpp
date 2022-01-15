

#include "TrainingTargetFactory.h"
#include "TrainingTargetObjectPool.h"
#include "TrainingTarget.h"

TrainingTargetFactory* TrainingTargetFactory::ptrInstance = nullptr;

TrainingTarget* TrainingTargetFactory::privCreateTarget(Vect a)
{
	TrainingTarget* Target = nullptr;

	if (ammo > 0) {
		Target = myTargetPool.GetTarget();


		Target->Initialize(a);


		ammo -= 1;
	}

	return Target;
}

void TrainingTargetFactory::privRecycleTarget(GameObject* b)
{
	myTargetPool.ReturnTarget(static_cast<TrainingTarget*>(b));
	ammo += 1;
}

void TrainingTargetFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
