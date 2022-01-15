#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"

void KeyboardEventManager::Register(Inputable* argIn, AZUL_KEY argKey, EVENT_TYPE argEv) {
	SingleKeyEventManager* tmpSKEM;

	//Create Manager for Key, if one doesn't exist
	if (storageMap.find(argKey) == storageMap.end()) {
		tmpSKEM = new SingleKeyEventManager(argKey);
		storageMap.insert(std::pair<AZUL_KEY,SingleKeyEventManager*>(argKey,tmpSKEM));
	}
	else {
		tmpSKEM = storageMap.find(argKey)->second;
	}

	//Pass Inputable and EVENT_TYPE to SKEM
	tmpSKEM->Register(argIn, argKey, argEv);
}

void KeyboardEventManager::Deregister(Inputable* argIn, AZUL_KEY argKey, EVENT_TYPE argEv) {
	storageMap.find(argKey)->second->Deregister(argIn, argKey, argEv);
}

void KeyboardEventManager::ProcessKeyEvents() {
	std::multimap<AZUL_KEY,SingleKeyEventManager*>::const_iterator it;
	for (it = storageMap.begin(); it != storageMap.end(); ++it) {
		it->second->ProcessKeyEvent();
	}
}

KeyboardEventManager::~KeyboardEventManager() {
	std::multimap<AZUL_KEY, SingleKeyEventManager*>::const_iterator it;
	for (it = storageMap.begin(); it != storageMap.end(); ++it) {
		delete it->second;
	}
}