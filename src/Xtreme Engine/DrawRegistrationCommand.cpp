#include "DrawRegistrationCommand.h"
#include "Drawable.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* argDr)
	: ptrDr(argDr)
{

}

void DrawRegistrationCommand::execute() {
	//ptrDr->SceneRegistration();
	DrawableAttorney::Registration::SceneRegistration(ptrDr);
}