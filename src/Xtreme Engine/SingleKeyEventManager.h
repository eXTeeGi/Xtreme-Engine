#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include "AzulCore.h"
#include "KeyboardEventManager.h"
#include <list>

class Inputable;

class SingleKeyEventManager
{
public:
	SingleKeyEventManager();
	SingleKeyEventManager(AZUL_KEY);
	~SingleKeyEventManager() {};
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;

	void Deregister(Inputable*, AZUL_KEY,KeyboardEventManager::EVENT_TYPE);
	void ProcessKeyEvent();
	void Register(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);


private:
	AZUL_KEY key;
	bool lastState;
	std::list<Inputable*> keyPressCol;
	std::list<Inputable*> keyReleaseCol;
};

#endif _SingleKeyEventManager