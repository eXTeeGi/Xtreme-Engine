#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Collidable;

class CollisionDeregistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionDeregistrationCommand() = delete;
	~CollisionDeregistrationCommand() {};
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand&) = delete;
	CollisionDeregistrationCommand& operator= (const CollisionDeregistrationCommand&) = delete;

	CollisionDeregistrationCommand(Collidable*);

	virtual void execute();

	Collidable* ptrCol;
};

#endif _CollisionDeregistrationCommand