#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "CollisionDispatch.h"
#include "CollisionVolumeBSphere.h"
#include "Collidable.h"
#include "XtremeMath.h"
#include "XtremeColors.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd)
	: pG(g), pDispatch(pd)
{ }

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG->GetColliderCollection();


	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		auto tmpIt = it1;
		tmpIt++;

		const CollisionVolume& bs1 = (*it1)->GetCollisionVolume();

		for (auto it2= tmpIt; it2 != Collection1.end(); it2++)
		{

			const CollisionVolume& bs2 = (*it2)->GetCollisionVolume();


			bool test_result = XtremeMath::Intersect((CollisionVolumeBSphere&)(*it1)->GetBSphere(), (CollisionVolumeBSphere&)(*it2)->GetBSphere());

			if (test_result)
			{
				test_result = XtremeMath::Intersect(bs1, bs2);

				if (test_result)
				{
					pDispatch->ProcessCallbacks(*it1, *it2);

					Visualizer::ShowCollisionVolume(bs1, Vect(1, 0, 0, 1));
					Visualizer::ShowCollisionVolume(bs2, Vect(1, 0, 0, 1));
				}
				else
				{
					Visualizer::ShowCollisionVolume(bs1, Vect(0, 0, 1, 1));
					Visualizer::ShowCollisionVolume(bs2, Vect(0, 0, 1, 1));
				}
			}
			else
			{
				Visualizer::ShowCollisionVolume(bs1, XtremeColors::Blue);
				Visualizer::ShowCollisionVolume(bs2, XtremeColors::Blue);
			}

			



			

		}
	}
}
