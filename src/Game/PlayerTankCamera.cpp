#include "PlayerTankCamera.h"
#include "..//Xtreme Engine/XtremeEngine.h"


PlayerTankCamera::PlayerTankCamera() {
	CamPos = Vect(50,10,100.0f);
	CamRot = Matrix(IDENTITY);
	CamUp =  Vect(0,1,0);
	CamDir = Vect(0,0,1);

	ptrCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	ptrCam->setViewport(0, 0, XtremeEngine::GetWidth() , XtremeEngine::GetHeight());
	ptrCam->setPerspective(35.0f, float(XtremeEngine::GetWidth()) / float(XtremeEngine::GetHeight()), 1.0f, 10000.0f);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();

	Updatable::SubmitUpdateRegistration();
}

PlayerTankCamera::PlayerTankCamera(Vect pos) {
	CamPos = Vect(0,10,-100.0f);
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);

	ptrCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	ptrCam->setViewport(0, 0, XtremeEngine::GetWidth(), XtremeEngine::GetHeight());
	ptrCam->setPerspective(35.0f, float(XtremeEngine::GetWidth()) / float(XtremeEngine::GetHeight()), 1.0f, 10000.0f);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target = pos;
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();

	//Updatable::SubmitUpdateRegistration();
}

PlayerTankCamera::~PlayerTankCamera() {
	/*delete CamPos;
	delete CamRot;
	delete CamUp;
	delete CamDir;*/
	//Updatable::SubmitUpdateDeregistration();
	delete ptrCam;
}

void PlayerTankCamera::Update() {
	
	// Cam translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	// Cam Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}
	

	// Update the camera settings
	ptrCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	ptrCam->updateCamera();
}

void PlayerTankCamera::updateTankPos(Vect pos, Matrix rot) {
	/*ptrCam->setOrientAndPosition(CamUp * rot, pos + CamDir * rot, pos +  Vect(0,400,0));
	ptrCam->updateCamera();*/
	CamRot = rot;
	Matrix ShipRotPos = rot * Matrix(TRANS, pos);  // This is the worldmat without scaling
	Vect vNewCamPos = Vect(0,0,0) * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = Vect(0, 20, -150) * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	ptrCam->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	ptrCam->updateCamera();
}