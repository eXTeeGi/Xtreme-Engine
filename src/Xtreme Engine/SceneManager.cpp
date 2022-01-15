#include "SceneManager.h"
#include "Scene.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeCommand.h"
#include "SceneAttorney.h"

SceneManager* SceneManager::ptrinstance;

SceneManager::SceneManager() {
	ChangeNullCmd = new SceneChangeNullCommand();
	ptrSceneChangeCmd = ChangeNullCmd;
}

void SceneManager::privDelete() {
	ptrCurrentScene->SceneEnd();
	delete ptrCurrentScene;

	delete ChangeNullCmd;

	delete ptrinstance;
	ptrinstance = nullptr;
}

void SceneManager::privDraw() {
	//ptrCurrentScene->Draw();
	SceneAttorney::GameLoop::Draw(ptrCurrentScene);
}

//void SceneManager::privDraw2D() {
//	//trCurrentScene->Draw2D();
//	SceneAttorney::GameLoop::Draw2D(ptrCurrentScene);
//
//}

Scene* SceneManager::privGetCurrentScene() {
	return ptrCurrentScene;
}

void SceneManager::privInitStartScene() {
	ptrCurrentScene->Initialize();
}

void SceneManager::privSetStartScene(Scene* argScene) {
	ptrCurrentScene = argScene;
	SceneAttorney::GameLoop::CreateGodCam(ptrCurrentScene);
}

void SceneManager::privUpdate() {
	ptrSceneChangeCmd->execute();

	//ptrCurrentScene->Update();
	SceneAttorney::GameLoop::Update(ptrCurrentScene);

}

void SceneManager::privSetNextScene(Scene* arg) {
	ptrSceneChangeCmd = new SceneChangeCommand(arg);
}

void SceneManager::privChangeScene(Scene* arg) {
	ptrCurrentScene->SceneEnd();
	SceneAttorney::GameLoop::runBroker(ptrCurrentScene);
	delete ptrCurrentScene;

	ptrCurrentScene = arg;
	ptrCurrentScene->Initialize();
	SceneAttorney::GameLoop::CreateGodCam(ptrCurrentScene);

	delete ptrSceneChangeCmd;
	ptrSceneChangeCmd = ChangeNullCmd;
}

TerrainObject* SceneManager::privGetTerrain() {
	return ptrCurrentScene->GetTerrain();
}