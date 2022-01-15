#ifndef _FPSCamera
#define _FPSCamera

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Camera;

class FPSCamera : public GameObject
{
public:
	FPSCamera();
	~FPSCamera();

	FPSCamera(Vect pos);

	void updateTankPos(Vect pos);

	virtual void Draw() {};

	Camera* getCameraPtr() { return ptrCam; };
	Vect getPos() { return CamPos; }
	Matrix getRot() { return CamRot; }

	void reorient(Matrix );
private:
	Camera* ptrCam;

	Vect CamPos;
	Matrix CamRot;
	Vect CamUp;
	Vect CamDir;
	float CamTranSpeed = 1;
	float CamRotSpeed = .005f;
};

#endif _FPSCamera