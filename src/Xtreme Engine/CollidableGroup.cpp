#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

CollidableGroup::CollidableGroup() {
	colAABB = new CollisionVolumeAABB();
}

CollidableGroup::~CollidableGroup() {
	delete colAABB;
}

void CollidableGroup::Register(Collidable* argCol, CollidableCollectionRef& argRef) {
	argRef = CollideCol.insert(CollideCol.end(), argCol);
}

void CollidableGroup::Deregister(const CollidableCollectionRef& arg) {
	CollideCol.erase(arg);
}

const std::list<Collidable*>& CollidableGroup::GetColliderCollection() {
	return CollideCol;
}

void CollidableGroup::CalculateAABB() {
	if (CollideCol.size() == 0) return;

	CollidableCollectionRef it = CollideCol.begin();
	Vect cMax;
	Vect cMin;

	//first
	CollisionVolumeAABB bsAABB;
	CollisionVolumeBSphere* itBS = &(CollisionVolumeBSphere&)((*it)->GetBSphere());
	bsAABB.ComputeData(*itBS);
	cMax = bsAABB.getCornerMax();
	cMin = bsAABB.getCornerMin();

	//others
	for (++it; it != CollideCol.end();++it) {
		itBS = &(CollisionVolumeBSphere&)((*it)->GetBSphere());
		bsAABB.ComputeData(*itBS);
		if (bsAABB.getCornerMax().X() > cMax.X()) cMax[X] = bsAABB.getCornerMax().X();
		if (bsAABB.getCornerMax().Y() > cMax.Y()) cMax[Y] = bsAABB.getCornerMax().Y();
		if (bsAABB.getCornerMax().Z() > cMax.Z()) cMax[Z] = bsAABB.getCornerMax().Z();
		if (bsAABB.getCornerMin().X() < cMin.X()) cMin[X] = bsAABB.getCornerMin().X();
		if (bsAABB.getCornerMin().Y() < cMin.Y()) cMin[Y] = bsAABB.getCornerMin().Y();
		if (bsAABB.getCornerMin().Z() < cMin.Z()) cMin[Z] = bsAABB.getCornerMin().Z();
	}

	//update
	colAABB->ComputeData(cMax, cMin);
}

CollisionVolumeAABB* CollidableGroup::getAABB() {
	return colAABB;
}