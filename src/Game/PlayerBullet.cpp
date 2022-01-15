#include "PlayerBullet.h"
#include "PlayerBulletFactory.h"

PlayerBullet::PlayerBullet() {
	SetColliderModel(pGObjLT->getModel(), VolumeType::BSPHERE);
	UpdateCollisionData(pGObjLT->getWorld());
	SetCollidableGroup<PlayerBullet>();
}

PlayerBullet::~PlayerBullet() {

}

void PlayerBullet::Initialize(Matrix argRot, Matrix argScale, Vect argPos) {



	// Creating matrices for in-world placement
	Matrix world;
	ShipRot = argRot;
	ShipPos = argPos;
	world = ShipScale * ShipRot * Matrix(TRANS, argPos);
	pGObjLT->SetWorld(world);

	GameObject::SubmitEntry();

	
}

void PlayerBullet::Collision(EnemyTank*) {
	//DebugMsg::out("Collision PlayerBullet with EnemyTank\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}
void PlayerBullet::Collision(RushTank*) {
	//DebugMsg::out("Collision PlayerBullet with RushTank\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}
void PlayerBullet::Collision(BossTank*) {
	//DebugMsg::out("Collision PlayerBullet with RushTank\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}
void PlayerBullet::Collision(Die*) {
	//DebugMsg::out("Collision PlayerBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void PlayerBullet::Collision(Rock*) {
	//DebugMsg::out("Collision PlayerBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void PlayerBullet::Collision(TrainingTarget*) {
	//DebugMsg::out("Collision PlayerBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void PlayerBullet::Collision(UFO*) {
	//DebugMsg::out("Collision PlayerBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void PlayerBullet::SceneExit() {
	PlayerBulletFactory::RecyclePlayerBullet(this);
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
}