#include "UpdateRegistrationCommand.h"
#include "Updatable.h"
#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* argUp) 
	: ptrUp(argUp) 
{

}

void UpdateRegistrationCommand::execute() {
	//ptrUp->SceneRegistration();
	UpdatableAttorney::Registration::SceneRegistration(ptrUp);
}