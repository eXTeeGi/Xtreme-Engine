#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* arg) 
	:ptrCol(arg)
{
	
}

void CollisionRegistrationCommand::execute() {
	//ptrCol->SceneRegistration();
	CollidableAttorney::Registration::SceneRegistration(ptrCol);
}