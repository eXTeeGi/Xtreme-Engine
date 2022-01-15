#include "CameraManager.h"
#include "XtremeEngine.h"
#include "GodCam.h"

CameraManager::CameraManager() {
	DefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	DefaultCamera->setViewport(0, 0, XtremeEngine::GetWidth(), XtremeEngine::GetHeight());
	DefaultCamera->setPerspective(35.0f, float(XtremeEngine::GetWidth()) / float(XtremeEngine::GetHeight()), 1.0f, 10000.0f);
	
	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	DefaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	DefaultCamera->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	SetCurrentCamera(DefaultCamera);

	TwoD = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	assert(TwoD);

	TwoD->setViewport(0, 0, XtremeEngine::GetWidth(), XtremeEngine::GetHeight());
	TwoD->setOrthographic(-0.5f * XtremeEngine::GetWidth(), 0.5f * XtremeEngine::GetWidth(), -0.5f * XtremeEngine::GetHeight(), 0.5f * XtremeEngine::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	TwoD->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	TwoD->updateCamera();

	
}

void CameraManager::createGod() {
	godObj = new GodCam();
}

CameraManager::~CameraManager() {
	delete DefaultCamera;
	delete TwoD;
	delete godObj;
}

Camera* CameraManager::GetCurrentCamera() {
	return camCurrent;
}

void CameraManager::SetCurrentCamera(Camera* argNewCam) {
	camCurrent = argNewCam;
}

Camera* CameraManager::GetCurrent2DCamera() {
	return TwoD;
}

void CameraManager::SwitchToGod() {
	notGod = camCurrent;
	camCurrent = godObj->getCameraPtr();

	Vect tmpUp;
	notGod->getUp(tmpUp);
	Vect tmpTarget;
	notGod->getLookAt(tmpTarget);
	Vect tmpDir;
	notGod->getDir(tmpDir);
	Vect tmpPos;
	notGod->getPos(tmpPos);

	godObj->SwitchTo(tmpUp, tmpTarget, tmpDir, tmpPos);
}

void CameraManager::SwitchFromGod() {
	camCurrent = notGod;
}