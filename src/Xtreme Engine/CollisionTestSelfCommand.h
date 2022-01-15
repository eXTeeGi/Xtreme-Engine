#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "AzulCore.h"
#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	CollisionTestSelfCommand() = default;
	~CollisionTestSelfCommand();
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = default;
	CollisionTestSelfCommand& operator= (const CollisionTestSelfCommand&) = delete;

	CollisionTestSelfCommand(CollidableGroup*, CollisionDispatchBase*);
	

	void execute();
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG;
};

#endif _CollisionTestSelfCommand