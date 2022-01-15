#include "Scene.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "SceneRegistrationBroker.h"
#include "KeyboardEventManager.h"
#include "CommandBase.h"
#include "CameraManager.h"
#include "VisualizerAttorney.h"
#include "TerrainObjectManager.h"
#include "TerrainObject.h"

Scene::Scene() {
	RegistrationBrkr = new SceneRegistrationBroker();
	UpdateMgr = new UpdatableManager();
	DrawMgr = new DrawableManager();
	AlarmMgr = new AlarmableManager();
	KBEventMgr = new KeyboardEventManager();
	cameraMan = new CameraManager();
	ColMgr = new CollisionManager();
	terrainObj = nullptr;
}

Scene::~Scene() {
	delete UpdateMgr;
	delete DrawMgr;
	delete AlarmMgr;
	delete KBEventMgr;
	delete cameraMan;
	delete ColMgr;
	delete RegistrationBrkr;
}

void Scene::runBroker() {
	RegistrationBrkr->ExecuteCommands();

}

void Scene::Update() {
	RegistrationBrkr->ExecuteCommands();

	KBEventMgr->ProcessKeyEvents();

	UpdateMgr->ProcessElements();

	ColMgr->ProcessCollisions();

	RegistrationBrkr->ExecuteCommands();

	AlarmMgr->ProcessAlarms();
}

void Scene::Draw() {
	if (terrainObj != nullptr) terrainObj->Draw(cameraMan);

	DrawMgr->ProcessElements();
}

//void Scene::Draw2D() {
//	DrawMgr->Process2DElements();
//}

void Scene::Register(Updatable* argUp, UpdatableManager::StorageListRef& argRef) {
	UpdateMgr->Register(argUp, argRef);
}

void Scene::Deregister(UpdatableManager::StorageListRef argRef) {
	UpdateMgr->Deregister(argRef);
}

void Scene::Register(Drawable* argDr, DrawableManager::StorageListRef& argRef) {
	DrawMgr->Register(argDr, argRef);
}

void Scene::Deregister(DrawableManager::StorageListRef argRef) {
	DrawMgr->Deregister(argRef);
}

void Scene::Register(float argT,Alarmable* argAl,AlarmableManager::ALARM_ID argID, AlarmableManager::StorageMapRef& argRef) {
	AlarmMgr->Register(argT, argAl, argID, argRef);
}

void Scene::Deregister(AlarmableManager::StorageMapRef& argRef) {
	AlarmMgr->Deregister(argRef);
}

void Scene::Register(Inputable* argIn, AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	KBEventMgr->Register(argIn, argKey, argEv);
}

void Scene::Deregister(Inputable* argIn, AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	KBEventMgr->Deregister(argIn, argKey, argEv);
}

//void Scene::Register(Collidable* arg) {
//	ColMgr->
//}


void Scene::SubmitCommand(CommandBase* argCmd) {
	RegistrationBrkr->addCommand(argCmd);
}

CollisionManager* Scene::GetCollisionManager() {
	return ColMgr;
}

void Scene::CreateGodCam() {
	cameraMan->createGod();
}

void Scene::SetTerrain(const char* const terrainKey) {
	terrainObj = TerrainObjectManager::Get(terrainKey);
}