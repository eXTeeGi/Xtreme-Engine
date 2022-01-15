#include "Rock.h"
#include "../Xtreme Engine/XtremeMath.h"
#include "PlayerTankManager.h"

Rock::Rock() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Rock"), ShaderManager::Get("TextureLight"), TextureManager::Get("Stone"), Color, LightPos);

	Matrix S = Matrix(SCALE, 50.0f, 50.0f, 50.0f);
	Matrix R = Matrix(ROT_Y, (float)(rand() % 6));
	Matrix T = Matrix(TRANS, Vect((float)(rand() % 6000) - 3000, 10.0f, (float)(rand() % 6000) - 3000));
	Matrix world = S * R * T;
	rot = R;
	scale = S;
	pGO->SetWorld(world);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();

	SetColliderModel(pGO->getModel(), VolumeType::OBB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<Rock>();

	pos = Vect(0, 0, 0);
}

Rock::Rock(Vect argPos) {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Rock"), ShaderManager::Get("TextureLight"), TextureManager::Get("Stone"), Color, LightPos);

	Matrix S = Matrix(SCALE, 50.0f, 50.0f, 50.0f);
	Matrix R = Matrix(ROT_Y, (float)(rand() % 6));
	Matrix T = Matrix(TRANS, argPos);
	Matrix world = S * R * T;
	rot = R;
	scale = S;
	pGO->SetWorld(world);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();

	SetColliderModel(pGO->getModel(), VolumeType::OBB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<Rock>();
	SubmitCollisionRegistration();

	pos = argPos;
}

Rock::~Rock() {
	delete pGO;
}

void Rock::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Rock::Update() {
	if (XtremeMath::EuclideanNorm(pos - PlayerTankManager::getPlayerTankPos()) < 1000) {
		if (!Collidable::isRegistered()) {
			SubmitCollisionRegistration();
		}
	}
	else if (Collidable::isRegistered()) {
		SubmitCollisionDeregistration();
	}

	UpdateCollisionData(pGO->getWorld());
}
