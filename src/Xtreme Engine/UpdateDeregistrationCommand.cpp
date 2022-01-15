#include "UpdateDeregistrationCommand.h"
#include "Updatable.h"
#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* argUp)
	: ptrUp(argUp)
{

}

void UpdateDeregistrationCommand::execute() {
	//ptrUp->SceneDeregistration();
	UpdatableAttorney::Registration::SceneDeregistration(ptrUp);
}