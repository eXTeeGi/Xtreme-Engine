#include "DrawableManager.h"
#include "Drawable.h"
#include "DrawableAttorney.h"
#include "VisualizerAttorney.h"

void DrawableManager::ProcessElements() {
	std::list<Drawable*>::const_iterator it;
	for (it = storageList.begin(); it != storageList.end(); ++it) {
		//(*it)->Draw();
		DrawableAttorney::GameLoop::Draw(*it);
	}

	VisualizerAttorney::Draw::VisualizeAll();

	for (it = storageList.begin(); it != storageList.end(); ++it) {
		//(*it)->Draw();
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
}

void DrawableManager::Process2DElements() {
	std::list<Drawable*>::const_iterator it;
	for (it = storageList.begin(); it != storageList.end(); ++it) {
		//(*it)->Draw();
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
}

void DrawableManager::Register(Drawable* argDr, StorageListRef& argRef) {
	//storageList.push_front(argUp);

	StorageListRef ref = storageList.insert(storageList.end(), argDr);
	argRef = ref;
}

void DrawableManager::Deregister(StorageListRef argRef) {
	storageList.erase(argRef);
}

DrawableManager::~DrawableManager() {

}