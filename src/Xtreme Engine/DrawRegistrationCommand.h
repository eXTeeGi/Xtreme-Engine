#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Drawable;

class DrawRegistrationCommand: public SceneRegistrationCommand
{
public:
	DrawRegistrationCommand(Drawable*);

	virtual void execute();

	Drawable* ptrDr;
};

#endif _DrawRegistrationCommand