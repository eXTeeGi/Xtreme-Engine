#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

#include "AzulCore.h"
#include "CommandBase.h"

class CollisionTestCommandBase : public CommandBase
{
public:
	CollisionTestCommandBase() {};
	virtual ~CollisionTestCommandBase() {};
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	CollisionTestCommandBase& operator= (const CollisionTestCommandBase&) = delete;
};

#endif _CollisionTestCommandBase