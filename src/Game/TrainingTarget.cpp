#include "TrainingTarget.h"
#include "EnemyTurret.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "PlayerTankManager.h"
#include "TrainingTargetFactory.h"
#include "..//Xtreme Engine///SoundPlayer.h"

TrainingTarget::TrainingTarget(Vect arg) {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("Target"), Color, LightPos);



	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 3.0f, 3.0f, 3.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);


	SetColliderModel(pGO->getModel(), VolumeType::AABB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<TrainingTarget>();
}

void TrainingTarget::Initialize(Vect arg) {
	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 30.0f, 30.0f, 30.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);


	GameObject::SubmitEntry();


	//SubmitCollisionRegistration();

}

TrainingTarget::~TrainingTarget() {
	delete pGO;
}

void TrainingTarget::Update() {


	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	UpdateCollisionData(pGO->getWorld());

}

void TrainingTarget::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void TrainingTarget::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
}

void TrainingTarget::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	TrainingTargetFactory::RecycleTarget(this);
	
}

void TrainingTarget::Collision(PlayerBullet*) {
	this->SubmitExit();
	SoundPlayer::playSound("Pop", ShipPos);

}