#ifndef _PlayerTankCamera
#define _PlayerTankCamera

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Camera;

class PlayerTankCamera : public GameObject
{
public:
	PlayerTankCamera();
	~PlayerTankCamera();

	PlayerTankCamera(Vect pos);

	void updateTankPos(Vect pos, Matrix rot);

	virtual void Update() override;
	virtual void Draw() {};

	Camera* getCameraPtr() { return ptrCam; };
	Matrix getRot() { return CamRot; }
private:
	Camera* ptrCam;

	Vect CamPos;
	Matrix CamRot;		
	Vect CamUp;			
	Vect CamDir;		
	float CamTranSpeed = 1;
	float CamRotSpeed = .03f;
};

#endif _PlayerTankCamera