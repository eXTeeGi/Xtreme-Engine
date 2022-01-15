#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionTestCommandBase.h"

int CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager() {
	MAX_COLLISION_GROUP = 100;

	for (int i = 0; i < MAX_COLLISION_GROUP; i++) {
		ColGroupCollection.push_back(nullptr);
	}
}

CollisionManager::~CollisionManager() {
	for (int i = 0; i < MAX_COLLISION_GROUP; i++) {
		if (ColGroupCollection[i] != nullptr)
			delete ColGroupCollection[i];
	}

	while (!colTestCommands.empty()) {
		delete colTestCommands.front();
		colTestCommands.pop_front();
	}
}

void CollisionManager::SetGroupForTypeID(CollisionManager::PWTypeID ind)
{
	if (ColGroupCollection[ind] == nullptr)
		ColGroupCollection[ind] = new CollidableGroup();
}

CollidableGroup* CollisionManager::GetColGroup(PWTypeID arg) {
	return ColGroupCollection.at(arg);
}

void CollisionManager::ProcessCollisions() {
	//Update Group AABB
	for (int git = 0; git < (int)ColGroupCollection.size(); ++git)
	{
		if (ColGroupCollection[git] != nullptr) ColGroupCollection[git]->CalculateAABB();
	}

	//Commence Testing
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); ++it)
	{
		(*it)->execute();
	}
}