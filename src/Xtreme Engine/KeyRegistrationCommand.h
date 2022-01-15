#ifndef _KeyRegistrationCommand
#define _KeyRegistrationCommand

#include "AzulCore.h"
#include "KeyboardEventManager.h"
#include "SceneRegistrationCommand.h"
class Inputable;

class KeyRegistrationCommand : public SceneRegistrationCommand
{
public:
	KeyRegistrationCommand(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);

	virtual void execute();

	Inputable* ptrIn;
	AZUL_KEY key;
	KeyboardEventManager::EVENT_TYPE ev;
};

#endif _KeyRegistrationCommand