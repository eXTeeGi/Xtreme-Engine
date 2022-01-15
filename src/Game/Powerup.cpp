#include "Powerup.h"
#include "PowerupFactory.h"
#include "PowerupManager.h"
#include "..//Xtreme Engine/XtremeColors.h"

Powerup::Powerup() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGOSpeed = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("SpeedBoost"),Color, LightPos);
	pGOCurr = pGOSpeed;
}

void Powerup::Initialize(Vect arg) {
	Matrix world;
	Scale.set(SCALE, 10.0f, 10.0f, 10.0f);
	Rot.set(IDENTITY);
	Pos = arg;
	Pos[Y] = 5;
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGOCurr->SetWorld(world);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	SetColliderModel(pGOCurr->getModel(), VolumeType::BSPHERE);
	UpdateCollisionData(pGOCurr->getWorld());
	SetCollidableGroup<Powerup>();
	SubmitCollisionRegistration();

	SubmitEntry();

	int itype = rand() % 1;
	switch (itype)
	{
	case 0:
		type = SPEEDBOOST;
		pGOCurr = pGOSpeed;

		break;
	default:
		break;
	}
}


Powerup::~Powerup() {
	delete pGOSpeed;
}

void Powerup::Update() {
}

void Powerup::Draw() {
	pGOCurr->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Powerup::Collision(PlayerTank*) {
	switch (type)
	{
	case Powerup::SPEEDBOOST:
		PowerupManager::speedBoost();
		break;
	default:
		break;
	}
	SubmitExit();
}

void Powerup::SceneExit() {
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	PowerupFactory::RecyclePowerup(this);
}