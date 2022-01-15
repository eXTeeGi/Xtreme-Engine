#ifndef _DrawableManager
#define _DrawableManager

#include "AzulCore.h"
#include <list>
class Drawable;

class DrawableManager
{
private:
	using StorageList = std::list<Drawable*>;
	StorageList storageList;

public:
	DrawableManager() = default;
	~DrawableManager();
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;

	void ProcessElements();
	void Process2DElements();

	using StorageListRef = StorageList::iterator;

	void Register(Drawable* up, StorageListRef&);
	void Deregister(StorageListRef);
};

#endif _DrawableManager