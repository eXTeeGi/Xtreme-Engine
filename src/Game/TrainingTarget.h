#ifndef _TrainingTarget
#define _TrainingTarget

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"

class PlayerBullet;

class TrainingTarget : public GameObject
{
public:
	TrainingTarget() = delete;
	TrainingTarget(Vect pos);
	~TrainingTarget();

	void Initialize(Vect pos);

	virtual void Update() override;
	virtual void Draw() override;
	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerBullet*);

	Vect& getPos() { return ShipPos; }


private:
	GraphicsObject_TextureLight* pGO;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix ShipScale;

};

#endif _TrainingTarget