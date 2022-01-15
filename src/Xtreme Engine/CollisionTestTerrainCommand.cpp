#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "CollisionDispatch.h"
#include "CollisionVolumeBSphere.h"
#include "Collidable.h"
#include "XtremeMath.h"
#include "XtremeColors.h"
#include "SceneManager.h"
#include "TerrainObject.h"


CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* g1)
	: pG1(g1)
{ }

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
	
}

void CollisionTestTerrainCommand::execute()
{

	TerrainObject* terrain = SceneManager::GetTerrain();
	const CollidableGroup::CollidableCollection& Collection = pG1->GetColliderCollection();

	for (auto it = Collection.begin(); it != Collection.end(); it++)
	{
		terrain->Intersect(*it);
	}



}
