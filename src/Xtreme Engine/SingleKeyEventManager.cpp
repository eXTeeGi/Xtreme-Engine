#include "SingleKeyEventManager.h"
#include "Inputable.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY argKey) {
	key = argKey;
	lastState = Keyboard::GetKeyState(key);
}

SingleKeyEventManager::SingleKeyEventManager() {
	lastState = Keyboard::GetKeyState(key);
}

void SingleKeyEventManager::Deregister(Inputable* argIn, AZUL_KEY, KeyboardEventManager::EVENT_TYPE argEv) {
	switch (argEv)
	{
	case (KeyboardEventManager::EVENT_TYPE::KEY_PRESS):
		keyPressCol.remove(argIn);
	case (KeyboardEventManager::EVENT_TYPE::KEY_RELEASE):
		keyReleaseCol.remove(argIn);
	default:
		break;
	}
}

void SingleKeyEventManager::ProcessKeyEvent() {
	//Check if state has changed
	if (Keyboard::GetKeyState(key) != lastState) {

		//Check if state is down or up
		if (Keyboard::GetKeyState(key)) {
			std::list<Inputable*>::const_iterator it;
			for (it = keyPressCol.begin(); it != keyPressCol.end(); ++it) {
				(*it)->KeyPressed(key);
			}
		}
		else {
			std::list<Inputable*>::const_iterator it;
			for (it = keyReleaseCol.begin(); it != keyReleaseCol.end(); ++it) {
				(*it)->KeyReleased(key);
			}
		}
		
	}

	//Save state
	lastState = Keyboard::GetKeyState(key);
}

void SingleKeyEventManager::Register(Inputable* argIn, AZUL_KEY, KeyboardEventManager::EVENT_TYPE argEv) {
	switch (argEv)
	{
	case (KeyboardEventManager::EVENT_TYPE::KEY_PRESS):
		keyPressCol.push_back(argIn);
		break;
	case (KeyboardEventManager::EVENT_TYPE::KEY_RELEASE):
		keyReleaseCol.push_back(argIn);
		break;
	default:
		break;
	}
}
