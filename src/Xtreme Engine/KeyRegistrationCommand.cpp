#include "KeyRegistrationCommand.h"
#include "InputableAttorney.h"
#include "Inputable.h"

KeyRegistrationCommand::KeyRegistrationCommand(Inputable* argIn, AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) 
	:ptrIn(argIn), key(argKey), ev(argEv)
{

}

void KeyRegistrationCommand::execute() {
	//ptrIn->SceneRegistration(key, ev);
	InputableAttorney::Registration::KeyRegistration(ptrIn, key, ev);
}