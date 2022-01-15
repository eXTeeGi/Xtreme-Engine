#include "BossTank.h"
#include "EnemyTurret.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "../Demo/Bullet.h"
#include "PlayerTankManager.h"
#include "EnemyBulletFactory.h"
#include "..//Xtreme Engine///ScreenLog.h"
#include "..//Xtreme Engine/XtremeMath.h"
#include "Die.h"
#include "Rock.h"
#include "WaveController.h"
#include "..//Xtreme Engine/SoundPlayer.h"
BossTank::BossTank() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Tank"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankGreen"), Color, LightPos);



	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipRot *= Matrix(ROT_Y, MATH_PI);
	ShipPos.set(Vect(0,0,200));
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	//Turret Stuff
	Vect ColorTurr(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPosTurr(1.0f, 1.0f, 1.0f, 1.0f);
	pGOTurr = new GraphicsObject_TextureLight(ModelManager::Get("Turret"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankGreen"), ColorTurr, LightPosTurr);
	Matrix worldTurr;
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrRot *= Matrix(ROT_Y, MATH_PI);
	TurrPos.set(0, 0, 0);
	worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

	SetColliderModel(pGO->getModel(), VolumeType::OBB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<BossTank>();

	lives = PlayerTankManager::getLives() + 3;

	GameObject::SubmitEntry();
}


BossTank::~BossTank() {
	delete pGO;
	delete pGOTurr;
}

void BossTank::Update() {

	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) {
		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			//ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
			if (ShipTransSpeed < maxSpeed) ShipTransSpeed += 0.05f;
			else if (ShipTransSpeed > maxSpeed) ShipTransSpeed = maxSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			//ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
			if (ShipTransSpeed > -maxSpeed) ShipTransSpeed -= 0.05f;
			else if (ShipTransSpeed < -maxSpeed) ShipTransSpeed = -maxSpeed;
		}
		else {
			ShipTransSpeed /= 1.1f;
		}

		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;

		// Ship Rotation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			ShipRot *= Matrix(ROT_Y, ShipRotAng/* * ShipTransSpeed*/);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			ShipRot *= Matrix(ROT_Y, -ShipRotAng/* * ShipTransSpeed*/);
		}
	}

	//bounds
	if (XtremeMath::EuclideanNorm(ShipPos - Vect(0, 0, 0)) > 3000) /*ShipRot *= Matrix(ROT_Y, MATH_PI);*/ {
		// ACTUALLY GOOD
		ShipPos += (Vect(0, ShipPos[Y], 0) - ShipPos).getNorm() * maxSpeed;
	}



	//ShipPos += Vect(0, 0, 1) * ShipRot * (ShipTransSpeed * WorS);
	//ShipRot *= Matrix(ROT_Y, -(ShipRotAng * AorD));
	//bounds


	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	//turret->MyUpdate(ShipPos);

	UpdateCollisionData(pGO->getWorld());

	//Turret
	TurrPos = ShipPos;
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) {
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
		{
			TurrRot *= Matrix(ROT_Y, TurrRotAng);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
		{
			TurrRot *= Matrix(ROT_Y, -TurrRotAng);
		}
	}
	Matrix worldturr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldturr);

}

void BossTank::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	pGOTurr->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void BossTank::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyboardEventManager::KEY_PRESS);

}

void BossTank::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	//if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

	//BossTankFactory::RecycleBossTank(this);
}

void BossTank::Collision(PlayerTank*) {
	//DebugMsg::out("Collision BossTank with PlayerTank\n");
}

void BossTank::Collision(PlayerBullet*) {
	//DebugMsg::out("Collision BossTank with PlayerBullet\n");


	--lives;
	if (lives <= 0) {
		GameObject::SubmitExit();
		WaveController::bossGone();
	}
}

void BossTank::Collision(Die* ) {
	
}

void BossTank::Collision(Rock* other) {
	Vect otherPos = other->getPos();

	// REALLY COOL, BUT BAD
	//ShipPos += (ShipPos-otherPos) * ShipTransSpeed;

	// ACTUALLY GOOD
	otherPos[Y] = ShipPos[Y];
	ShipPos += (ShipPos - otherPos).getNorm() * maxSpeed;

	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	this->UpdateCollisionData(world);
}


void BossTank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ARROW_UP:
		
			EnemyBulletFactory::CreateEnemyBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));
			//SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f);
			SoundPlayer::playSound("BAM", ShipPos);


		break;

	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}