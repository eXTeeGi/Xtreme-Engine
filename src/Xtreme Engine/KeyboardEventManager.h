#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include <map>
#include "AzulCore.h"

class Inputable;
class SingleKeyEventManager;

class KeyboardEventManager
{
public:
	enum EVENT_TYPE
	{
		KEY_PRESS,
		KEY_RELEASE
	};
private:
	using StorageMap = std::multimap<AZUL_KEY, SingleKeyEventManager*>;
	StorageMap storageMap;

	// A reminder of my stupidity...
	/*if (storageMap.find(argKey) == storageMap.end()) {
		tmpSKEM = new SingleKeyEventManager(argKey);
		storageMap.insert(std::pair<AZUL_KEY, SingleKeyEventManager*>(argKey, tmpSKEM));
	}*/

public:

	KeyboardEventManager() = default;
	~KeyboardEventManager();
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;

	void ProcessKeyEvents();

	using StorageMapRef = StorageMap::iterator;

	void Register(Inputable* , AZUL_KEY, EVENT_TYPE);
	void Deregister(Inputable* , AZUL_KEY ,EVENT_TYPE);


};

#endif _KeyboardEventManager