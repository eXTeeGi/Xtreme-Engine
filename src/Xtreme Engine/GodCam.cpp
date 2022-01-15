#include "GodCam.h"
#include "..//Xtreme Engine/XtremeEngine.h"


GodCam::GodCam() {
	CamPos = Vect(50, 10, 100.0f);
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);

	ptrCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	ptrCam->setViewport(0, 0, XtremeEngine::GetWidth(), XtremeEngine::GetHeight());
	ptrCam->setPerspective(35.0f, float(XtremeEngine::GetWidth()) / float(XtremeEngine::GetHeight()), 1.0f, 10000.0f);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();

	Updatable::SubmitUpdateRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyboardEventManager::EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyboardEventManager::EVENT_TYPE::KEY_RELEASE);
}

GodCam::GodCam(Vect pos) {
	CamPos = Vect(0, 10, -100.0f);
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);

	ptrCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	ptrCam->setViewport(0, 0, XtremeEngine::GetWidth(), XtremeEngine::GetHeight());
	ptrCam->setPerspective(35.0f, float(XtremeEngine::GetWidth()) / float(XtremeEngine::GetHeight()), 1.0f, 5000.0f);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target = pos;
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();

	//Updatable::SubmitUpdateRegistration();
}

GodCam::~GodCam() {
	/*delete CamPos;
	delete CamRot;
	delete CamUp;
	delete CamDir;*/
	//Updatable::SubmitUpdateDeregistration();
	delete ptrCam;
}

void GodCam::Update() {
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT) && !Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) {
		// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
		}

		// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
		{
			CamRot *= Matrix(ROT_Y, CamRotSpeed);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
		{
			CamRot *= Matrix(ROT_Y, -CamRotSpeed);
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
		{
			CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
		{
			CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
		}
	}
	

	// Update the camera settings
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();

}

void GodCam::SwitchTo(Vect argUp, Vect argTarget, Vect argDir, Vect argPos) {
	/*CamUp = argUp;
	CamDir = argDir;
	CamPos = argPos;
	CamRot.set(ROT_ORIENT, argTarget - argPos, argUp);
	ptrCam->setOrientAndPosition(argUp * CamRot, argPos + argDir * CamRot, argPos);
	ptrCam->updateCamera();*/

	CamPos = Vect(0, 10, -100.0f);
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();
}

void GodCam::KeyPressed(AZUL_KEY k) {
	switch (k)
	{
	case KEY_LEFT_SHIFT:
		SceneManager::GetCurrentScene()->getCamMan()->SwitchToGod();
		break;
	default:
		break;
	}
}

void GodCam::KeyReleased(AZUL_KEY k) {
	switch (k)
	{
	case KEY_LEFT_SHIFT:
		SceneManager::GetCurrentScene()->getCamMan()->SwitchFromGod();
		break;
	default:
		break;
	}
}