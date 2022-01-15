#include "DrawDeregistrationCommand.h"
#include "Drawable.h"
#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* argDr)
	: ptrDr(argDr)
{

}

void DrawDeregistrationCommand::execute() {
	//ptrDr->SceneDeregistration();
	DrawableAttorney::Registration::SceneDeregistration(ptrDr);
}