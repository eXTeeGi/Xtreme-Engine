#include "FPSCamera.h"
#include "..//Xtreme Engine/XtremeEngine.h"


FPSCamera::FPSCamera() {
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

}

FPSCamera::FPSCamera(Vect pos) {
	CamPos = Vect(0, 10, -100.0f);
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

FPSCamera::~FPSCamera() {
	/*delete CamPos;
	delete CamRot;
	delete CamUp;
	delete CamDir;*/
	//Updatable::SubmitUpdateDeregistration();
	delete ptrCam;
}


void FPSCamera::updateTankPos(Vect pos) {
	/*ptrCam->setOrientAndPosition(CamUp * rot, pos + CamDir * rot, pos +  Vect(0,400,0));
	ptrCam->updateCamera();*/

	

	// Cam translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		CamRot *= Matrix(RotAxisAngleType::ROT_AXIS_ANGLE,CamRot.get(ROW_0), -CamRotSpeed * 2);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		CamRot *= Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, CamRot.get(ROW_0),  CamRotSpeed * 2);
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

	// Cam Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed * 5);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed * 5);
	}

	CamPos = pos;

	Matrix ShipRotPos = CamRot * Matrix(TRANS, pos);  // This is the worldmat without scaling
	Vect vNewCamPos = Vect(0, 20, 0) + pos;/*  + (* ShipRotPos)*/	// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = Vect(0, 20, 0) + pos  + (Vect(0, 0, 1) * CamRot);   // This moves the look-at point relative to ship's position and rotation

	ptrCam->setOrientAndPosition(CamRot.get(ROW_1), vNewLookAt, vNewCamPos);
	ptrCam->updateCamera();
}

void FPSCamera::reorient(Matrix rot) {
	CamRot = rot;

}