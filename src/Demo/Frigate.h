#ifndef _Frigate
#define _Frigate

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <string>

#include "fmod_ALL.h"

class WorldPlane;
class CollisionVolumeBSphere;

class Frigate : public GameObject
{
public:
	Frigate();
	~Frigate();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Alarm0() override;
	virtual void Alarm1() override;

	virtual void Collision(Collidable*) {};
	virtual void Collision(WorldPlane*);
	virtual void Collision(Frigate*) {
		//
	};

	virtual void CollisionTerrain();


	virtual void SceneEntry();
	virtual void KeyPressed(AZUL_KEY);

	Vect getPos() { return ShipPos; }
	CollisionVolumeBSphere& getBSphere();
	void orient(Vect& up);

private:
	GraphicsObject_TextureLight* pGObjLT;
	//GraphicsObject_WireframeConstantColor* pGObjWF;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	bool BsphereToggle = false;

	//personal project prototype
	GLbyte* pixels;
	Texture* pRTT;
	std::vector<Texture*> pRTTlist;
	int frame = 0;
	GLuint TID;

	FMOD::System* system;
	FMOD::Sound* testSound;
	FMOD_CREATESOUNDEXINFO* exInfo;
	FMOD::Channel* testChannel;
	FMOD::DSP* testDsp;

	//listener
	FMOD_VECTOR* fvPos;
	FMOD_VECTOR* fvVel;
	FMOD_VECTOR* fvFor;
	FMOD_VECTOR* fvUp;

	//source
	FMOD_VECTOR* fvPosS;
	FMOD_VECTOR* fvVelS;
};

#endif _Frigate