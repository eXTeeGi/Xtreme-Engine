#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>
#include "CollisionDispatch.h"
#include "CollisionDispatchBase.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"

class CollidableGroup;
class CollisionTestCommandBase;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator= (const CollisionManager&) = delete;

	using PWTypeID = int;
	static const PWTypeID PWID_UNDEFINED = -1;

private:
	static PWTypeID TypeIDNextNumber;

	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection ColGroupCollection;

	int MAX_COLLISION_GROUP;

	void SetGroupForTypeID(CollisionManager::PWTypeID ind);

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCommands;


public:
	//using CollidableCollectionRef = CollidableGroupCollection::iterator;

	template <typename C>
	PWTypeID GetTypeID()
	{
		static PWTypeID myTypeID = TypeIDNextNumber++;

		SetGroupForTypeID(myTypeID);

		//DebugMsg::out("Type ID: %i\n", myTypeID);
		return myTypeID;
	}

	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, (CollisionDispatchBase*)pDispatch));
	}

	template< typename C>
	void SetCollisionSelf()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C>()];

		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		colTestCommands.push_back(new CollisionTestSelfCommand(pg1, (CollisionDispatchBase*)pDispatch));
	}

	template< typename C>
	void SetCollisionTerrain()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C>()];

		colTestCommands.push_back(new CollisionTestTerrainCommand(pg1));
	}

	void ProcessCollisions();

	CollidableGroup* GetColGroup(PWTypeID);
};


#endif _CollisionManager