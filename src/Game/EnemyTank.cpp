#include "EnemyTank.h"
#include "EnemyTurret.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "../Demo/Bullet.h"
#include "PlayerTankManager.h"
#include "EnemyTankFactory.h"
#include "EnemyBulletFactory.h"
#include "..//Xtreme Engine///ScreenLog.h"
#include "..//Xtreme Engine/XtremeMath.h"
#include "Die.h"
#include "Rock.h"
#include "../Xtreme Engine///SoundPlayer.h"

EnemyTank::EnemyTank(Vect arg) {
	Vect Color(1.0f, 0.1f, 0.1f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Tank"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"), Color, LightPos);



	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	//Turret Stuff
	Vect ColorTurr(1.0f, 0.1f, 0.1f, 1.0f);
	Vect LightPosTurr(1.0f, 1.0f, 1.0f, 1.0f);
	pGOTurr = new GraphicsObject_TextureLight(ModelManager::Get("Turret"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"), ColorTurr, LightPosTurr);
	Matrix worldTurr;
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

	SetColliderModel(pGO->getModel(), VolumeType::AABB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<EnemyTank>();
}

void EnemyTank::Initialize(Vect arg) {
	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	//Turret Stuff
	Matrix worldTurr;
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

	GameObject::SubmitEntry();

	
	//SubmitCollisionRegistration();

}

EnemyTank::~EnemyTank() {
	delete pGO;
	delete pGOTurr;
}

void EnemyTank::Update() {
	
	if (XtremeMath::EuclideanNorm(ShipPos - Vect(0, 0, 0)) > 3000) /*ShipRot *= Matrix(ROT_Y, MATH_PI);*/ {
		// ACTUALLY GOOD
		ShipPos += (Vect(0, ShipPos[Y], 0) - ShipPos).getNorm() * maxSpeed;
	}
	else {
		// Ship translation movement (not using time-based values for simplicity)
		if (WorS != 0)
		{
			//ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
			if (abs(ShipTransSpeed) < maxSpeed) ShipTransSpeed += 0.05f * WorS;
		}
		else {
			ShipTransSpeed /= 1.1f;
		}

		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;

		// Ship Rotation movement (not using time-based values for simplicity)

		ShipRot *= Matrix(ROT_Y, ShipRotAng/* * ShipTransSpeed*/ * AorD);
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
	TurrRot.set(ROT_ORIENT, PlayerTankManager::getPlayerTankPos() - TurrPos, Vect(0, 1, 0));
	Matrix worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

}

void EnemyTank::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	pGOTurr->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void EnemyTank::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, (float)(rand() % 4) + 6.0f);
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_1) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, (float)(rand() % 4) + 1.0f);
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_2) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_2, (float)(rand()%4) + 1.0f);
	WorS = 0;
	AorD = 0;
}

void EnemyTank::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

	EnemyTankFactory::RecycleEnemyTank(this);

}

void EnemyTank::Collision(PlayerTank*) {
	//DebugMsg::out("Collision EnemyTank with PlayerTank\n");
}

void EnemyTank::Collision(PlayerBullet*) {
	//DebugMsg::out("Collision EnemyTank with PlayerBullet\n");


	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_1) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_2) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_2);
	//else DebugMsg::out("Failed to submit deregistration.");
	GameObject::SubmitExit();
	SoundPlayer::playSound("Explosion", ShipPos);

}

void EnemyTank::Collision(Die* other) {
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

void EnemyTank::Collision(Rock* other) {
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


void EnemyTank::Alarm0() {
	//if (getRegState() == GameObject::RegistrationState::CURRENTLY_REGISTERED) {
		//BulletFactory::CreateBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));
	if (XtremeMath::EuclideanNorm(ShipPos - PlayerTankManager::getPlayerTankPos()) < 1000) {
		EnemyBulletFactory::CreateEnemyBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));
		SoundPlayer::playSound("BAM", ShipPos);
	}
		

		if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, (float)(rand() % 4) + 1.0f);
		//else DebugMsg::out("Failed to submit registration.");
	//}
	

}

void EnemyTank::Alarm1() {
	
	if (rand() % 10 == 0) WorS = 0;
	else {
		Vect turrDir = TurrRot.get(ROW_2);
		Vect forward = ShipRot.get(ROW_2);
		Vect backwards = forward * -1;
		if (turrDir.getAngle(forward) < turrDir.getAngle(backwards)) {
			WorS = 1;
		}
		else WorS = -1;
	}
	

	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_1) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1,  1.0f);

}

void EnemyTank::Alarm2() {
	//AorD = rand() % 3 - 1;

	if (XtremeMath::EuclideanNorm(ShipPos - PlayerTankManager::getPlayerTankPos()) < 100 || rand() % 3 == 0) AorD = 0;
	else {
		Vect turrDir = TurrRot.get(ROW_2);
		Vect right = ShipRot.get(ROW_0);
		Vect left = right * -1;
		if (turrDir.getAngle(right) < turrDir.getAngle(left)) {
			AorD = 1;
		}
		else AorD = -1;
	}
	AorD *= WorS;

	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_2) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_2, 0.3f);

}