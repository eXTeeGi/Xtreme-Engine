#include "KeyDeregistrationCommand.h"
#include "InputableAttorney.h"
#include "Inputable.h"

KeyDeregistrationCommand::KeyDeregistrationCommand(Inputable* argIn, AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv)
	:ptrIn(argIn), key(argKey), ev(argEv)
{

}

void KeyDeregistrationCommand::execute() {
	//ptrIn->SceneDeregistration(key, ev);
	InputableAttorney::Registration::KeyDeregistration(ptrIn, key, ev);
}