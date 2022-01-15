#include "EnemyBullet.h"
#include "EnemyBulletFactory.h"

EnemyBullet::EnemyBullet() {
	SetColliderModel(pGObjLT->getModel(),VolumeType::BSPHERE);
	UpdateCollisionData(pGObjLT->getWorld());
	SetCollidableGroup<EnemyBullet>();
}

EnemyBullet::~EnemyBullet() {

}

void EnemyBullet::Initialize(Matrix argRot, Matrix argScale, Vect argPos) {



	// Creating matrices for in-world placement
	Matrix world;
	ShipRot = argRot;
	ShipPos = argPos;
	world = ShipScale * ShipRot * Matrix(TRANS, argPos);
	pGObjLT->SetWorld(world);

	GameObject::SubmitEntry();

	ShipTransSpeed = 5;
}

void EnemyBullet::Collision(PlayerTank*) {
	//DebugMsg::out("Collision EnemyBullet with PlayerTank\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void EnemyBullet::Collision(Die*) {
	//DebugMsg::out("Collision EnemyBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void EnemyBullet::Collision(Rock*) {
	//DebugMsg::out("Collision EnemyBullet with Die\n");

	ShipPos = Vect(0, -100, 0);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);
	UpdateCollisionData(pGObjLT->getWorld());

	if (getRegState() == RegistrationState::CURRENTLY_REGISTERED) GameObject::SubmitExit();
}

void EnemyBullet::SceneExit() {
	EnemyBulletFactory::RecycleEnemyBullet(this);
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
}