#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "AzulCore.h"
#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
public:
	CollisionTestTerrainCommand() = default;
	~CollisionTestTerrainCommand();
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = default;
	CollisionTestTerrainCommand& operator= (const CollisionTestTerrainCommand&) = delete;

	CollisionTestTerrainCommand(CollidableGroup*);

	void execute();
private:
	CollidableGroup* pG1;
};

#endif _CollisionTestTerrainCommand