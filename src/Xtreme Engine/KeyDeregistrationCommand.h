#ifndef _KeyDeregistrationCommand
#define _KeyDeregistrationCommand

#include "AzulCore.h"
#include "KeyboardEventManager.h"
#include "SceneRegistrationCommand.h"
class Inputable;

class KeyDeregistrationCommand : public SceneRegistrationCommand
{
public:
	KeyDeregistrationCommand(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);

	virtual void execute();

	Inputable* ptrIn;
	AZUL_KEY key;
	KeyboardEventManager::EVENT_TYPE ev;
};

#endif _KeyDeregistrationCommand