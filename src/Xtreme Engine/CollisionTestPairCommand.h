#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "AzulCore.h"
#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	CollisionTestPairCommand() = default;
	~CollisionTestPairCommand();
	CollisionTestPairCommand(const CollisionTestPairCommand&) = default;
	CollisionTestPairCommand& operator= (const CollisionTestPairCommand&) = delete;

	CollisionTestPairCommand(CollidableGroup*, CollidableGroup*, CollisionDispatchBase*);
	
	void execute();
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	CollidableGroup* pG2;
};

#endif _CollisionTestPairCommand