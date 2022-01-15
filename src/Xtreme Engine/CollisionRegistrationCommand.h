#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Collidable;

class CollisionRegistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionRegistrationCommand() = delete;
	~CollisionRegistrationCommand() {};
	CollisionRegistrationCommand(const CollisionRegistrationCommand&) = delete;
	CollisionRegistrationCommand& operator= (const CollisionRegistrationCommand&) = delete;

	CollisionRegistrationCommand(Collidable*);

	virtual void execute();

	Collidable* ptrCol;
};

#endif _CollisionRegistrationCommand