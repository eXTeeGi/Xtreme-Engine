#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "CollisionDispatch.h"
#include "CollisionVolumeBSphere.h"
#include "Collidable.h"
#include "XtremeMath.h"
#include "XtremeColors.h"


CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
	: pG1(g1), pG2(g2), pDispatch(pd)
{ }

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& Collection2 = pG2->GetColliderCollection();

	//1
	bool test_result = XtremeMath::Intersect(*pG1->getAABB(),*pG2->getAABB());

	if (test_result)
	{
		for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
		{
			//2
			test_result = XtremeMath::Intersect((CollisionVolumeBSphere&)(*it1)->GetBSphere(), *pG2->getAABB());

			if (test_result)
			{
				const CollisionVolume& bs1 = (*it1)->GetCollisionVolume();

				for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
				{
					//3
					test_result = XtremeMath::Intersect((CollisionVolumeBSphere&)(*it1)->GetBSphere(), (CollisionVolumeBSphere&)(*it2)->GetBSphere());

					if (test_result)
					{
						const CollisionVolume& bs2 = (*it2)->GetCollisionVolume();

						//4
						test_result = XtremeMath::Intersect(bs1, bs2);


						if (test_result)
						{
							pDispatch->ProcessCallbacks(*it1, *it2);

							Visualizer::ShowCollisionVolume(bs1, XtremeColors::Red);
							Visualizer::ShowCollisionVolume(bs2, XtremeColors::Red);
						}
						else
						{
							Visualizer::ShowCollisionVolume(bs1, XtremeColors::Blue);
							Visualizer::ShowCollisionVolume(bs2, XtremeColors::Blue);
						}
					}
					else
					{
						Visualizer::ShowCollisionVolume((*it1)->GetBSphere(), XtremeColors::Blue);
						Visualizer::ShowCollisionVolume((*it2)->GetBSphere(), XtremeColors::Blue);
					}

					
				}
			}
			else
			{
				Visualizer::ShowCollisionVolume((*it1)->GetBSphere(), XtremeColors::Blue);
				Visualizer::ShowCollisionVolume((CollisionVolume&)* pG2->getAABB(), XtremeColors::Blue);
			}

			
		}
	}
	else
	{
		Visualizer::ShowCollisionVolume((CollisionVolume&)*pG1->getAABB(), XtremeColors::Blue);
		Visualizer::ShowCollisionVolume((CollisionVolume&)*pG2->getAABB(), XtremeColors::Blue);
	}

	
}
