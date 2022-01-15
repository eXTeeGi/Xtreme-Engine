#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Drawable;

class DrawDeregistrationCommand: public SceneRegistrationCommand
{
public:
	DrawDeregistrationCommand(Drawable*);

	virtual void execute();

	Drawable* ptrDr;
};

#endif _DrawDeregistrationCommand