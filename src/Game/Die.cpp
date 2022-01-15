#include "Die.h"
#include "../Xtreme Engine/XtremeMath.h"
#include "PlayerTankManager.h"
#include "Rock.h"
#include "AmmoPickup.h"
#include "AmmoPickupFactory.h"
#include "PowerupFactory.h"
#include "PowerupManager.h"
#include "EnemyTank.h"
#include "BossTank.h"
#include "TrainingTarget.h"
#include "..//Xtreme Engine///SoundPlayer.h"

Die::Die() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("CubeTest"), Color, LightPos);

	Matrix S = Matrix(SCALE, 100.0f, 100.0f, 100.0f);
	Matrix R = Matrix(ROT_Y,(float)(rand()%6));
	Matrix T = Matrix(TRANS, Vect((float)(rand()%6000)-3000, 10.0f, (float)(rand() % 6000) - 3000));
	Matrix world = S *R* T;
	rot = R;
	scale = S;
	pGO->SetWorld(world);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();

	SetColliderModel(pGO->getModel(), VolumeType::OBB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<Die>();
	SoundPlayer::registerForOcclusion(this);
	pos = Vect(0, 0, 0);
	HP = 4;
}

Die::Die(Vect argPos) {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("CubeTest"), Color, LightPos);

	Matrix S = Matrix(SCALE, 100.0f, 100.0f, 100.0f);
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
	SetCollidableGroup<Die>();
	SubmitCollisionRegistration();
	SoundPlayer::registerForOcclusion(this);

	SubmitEntry();

	pos = argPos;
	HP = 4;
}

Die::~Die() {
	SoundPlayer::deregisterForOcclusion(this);
	delete pGO;
}

void Die::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Die::Update() {
	if (XtremeMath::EuclideanNorm(pos - PlayerTankManager::getPlayerTankPos()) < 2000) {
		if (!Collidable::isRegistered()) {
			SubmitCollisionRegistration();
		}
	}
	else if (Collidable::isRegistered()) {
		SubmitCollisionDeregistration();
	}

	UpdateCollisionData(pGO->getWorld());
}

void Die::Collision(PlayerTank*) {
	Vect otherPos = PlayerTankManager::getPlayerTankPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 8.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(EnemyTank* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 8.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(BossTank* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 8.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(Die* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 4.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(Rock* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 4.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(TrainingTarget* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = pos[Y];
	pos += (pos - otherPos).getNorm() * 4.0f;

	// Spaceship adjust matrix
	Matrix world = scale * rot * Matrix(TRANS, pos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}

void Die::Collision(PlayerBullet*) {
	--HP;
	if (HP <= 0) {
		SubmitExit();
		if (rand() % PowerupManager::getProbability() == 0) {
			PowerupFactory::CreatePowerup(pos);
			PowerupManager::addProbability();
		}
		else {
			AmmoPickupFactory::CreateAmmoPickup(pos);
			PowerupManager::subProbability();
		}
		SoundPlayer::playSound("Pop", pos);

		
	}
}

void Die::Collision(EnemyBullet*) {
	--HP;
	if (HP <= 0) {
		SubmitExit();
		//new AmmoPickup(pos[X],pos[Z]);
		int itype = rand() % 2;
		switch (itype)
		{
		case 0:
			AmmoPickupFactory::CreateAmmoPickup(pos);
			break;
		case 1:
			PowerupFactory::CreatePowerup(pos);
			break;
		default:
			break;
		}

	}
}

void Die::SceneExit() {
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();


}

void Die::SceneEntry() {

}