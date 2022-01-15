#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* arg)
	:ptrCol(arg)
{

}

void CollisionDeregistrationCommand::execute() {
	//ptrCol->SceneDeregistration();
	CollidableAttorney::Registration::SceneDeregistration(ptrCol);
}