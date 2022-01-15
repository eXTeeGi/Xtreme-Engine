#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>
class Updatable;

class UpdatableManager
{
private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;

	


public:
	UpdatableManager() = default;
	~UpdatableManager();
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;

	void ProcessElements();
	
	using StorageListRef = StorageList::iterator;

	void Register(Updatable* up, StorageListRef&);
	void Deregister(StorageListRef);

	
};

#endif _UpdatableManager