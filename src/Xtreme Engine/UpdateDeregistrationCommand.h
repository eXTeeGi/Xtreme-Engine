#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Updatable;

class UpdateDeregistrationCommand: public SceneRegistrationCommand
{
public:
	UpdateDeregistrationCommand(Updatable*);

	virtual void execute();

	Updatable* ptrUp;
};

#endif _UpdateDeregistrationCommand