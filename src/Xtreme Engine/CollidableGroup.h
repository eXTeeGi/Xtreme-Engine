#ifndef _CollidableGroup
#define _CollidableGroup

#include "CollisionManager.h"
#include <list>

class Collidable;
class CollisionVolumeAABB;

class CollidableGroup
{
private:
	
public:
	CollidableGroup();
	~CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator= (const CollidableGroup&) = delete;

	using CollidableCollection  = std::list<Collidable*>;
	CollidableCollection CollideCol;

	using CollidableCollectionRef = CollidableCollection::iterator;

	void Deregister(const CollidableCollectionRef&);
	const CollidableCollection& GetColliderCollection();
	void Register(Collidable*, CollidableCollectionRef&);

	void CalculateAABB();
	CollisionVolumeAABB* getAABB();

private:
	CollisionVolumeAABB* colAABB;
};

#endif _CollidableGroup