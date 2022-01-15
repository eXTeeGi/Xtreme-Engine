#ifndef _GodCam
#define _GodCam

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
class Camera;

class GodCam : public GameObject
{
public:
	GodCam();
	~GodCam();
	GodCam(const GodCam&) = delete;
	GodCam& operator= (const GodCam&) = delete;

	GodCam(Vect pos);

	void SwitchTo(Vect argUp, Vect argTarget, Vect argDir, Vect argPos);

	virtual void Update() override;
	virtual void Draw() {};
	virtual void KeyPressed(AZUL_KEY) override;
	virtual void KeyReleased(AZUL_KEY) override;

	Camera* getCameraPtr() { return ptrCam; };
private:
	Camera* ptrCam;

	Vect CamPos;
	Matrix CamRot;
	Vect CamUp;
	Vect CamDir;
	float CamTranSpeed = 3;
	float CamRotSpeed = .03f;
};

#endif _GodCam