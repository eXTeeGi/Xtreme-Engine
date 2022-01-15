#include "UpdatableManager.h"
#include "Updatable.h"
#include "UpdatableAttorney.h"

void UpdatableManager::ProcessElements() {
	std::list<Updatable*>::const_iterator it;
	for (it = storageList.begin(); it != storageList.end(); ++it) {
		//(*it)->Update();
		UpdatableAttorney::GameLoop::Update(*it);
	}
}

void UpdatableManager::Register(Updatable* up, StorageListRef& argRef) {
	/*StorageListRef ref = storageList.insert(storageList.end(), up);
	up->setRef(ref);*/

	//up->setRef( storageList.insert(storageList.end(), up) );

	//storageList.insert(storageList.end(), up);

	//argRef = storageList.insert(storageList.end(), up);

	StorageListRef ref = storageList.insert(storageList.end(), up);
	argRef = ref;

}

void UpdatableManager::Deregister(StorageListRef argRef) {
	storageList.erase(argRef);
}

UpdatableManager::~UpdatableManager() {
	
}