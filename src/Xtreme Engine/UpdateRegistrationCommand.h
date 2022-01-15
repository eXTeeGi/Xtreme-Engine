#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class Updatable;

class UpdateRegistrationCommand: public SceneRegistrationCommand
{
public:
	UpdateRegistrationCommand(Updatable*);

	virtual void execute();

	Updatable* ptrUp;
};

#endif _UpdateRegistrationCommand