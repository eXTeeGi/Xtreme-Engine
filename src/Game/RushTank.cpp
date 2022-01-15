#include "RushTank.h"
#include "EnemyTurret.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "../Demo/Bullet.h"
#include "PlayerTankManager.h"
#include "RushTankFactory.h"
#include "EnemyBulletFactory.h"
#include "..//Xtreme Engine///ScreenLog.h"
#include "..//Xtreme Engine/XtremeMath.h"
#include "..//Xtreme Engine/SoundPlayer.h"

RushTank::RushTank(Vect arg) {
	Vect Color(1.0f, 0.1f, 0.1f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("t99tank"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"), Color, LightPos);



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
	pGOTurr = new GraphicsObject_TextureLight(ModelManager::Get("t99turret"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"), ColorTurr, LightPosTurr);
	Matrix worldTurr;
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

	SetColliderModel(pGO->getModel(), VolumeType::AABB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<RushTank>();
}

void RushTank::Initialize(Vect arg) {
	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(ROT_Y,(float)(rand() % 360));
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

RushTank::~RushTank() {
	delete pGO;
	delete pGOTurr;
}

void RushTank::Update() {

	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);


	UpdateCollisionData(pGO->getWorld());

	//Turret
	TurrPos = ShipPos +  Vect(0,16,0);
	TurrRot.set(ROT_ORIENT, (PlayerTankManager::getPlayerTankPos()+Vect(0, TurrPos[y],0)) - TurrPos, Vect(0, 1, 0));
	Matrix worldTurr = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGOTurr->SetWorld(worldTurr);

	//ScreenLog::Add("EnemySpeed: %3.1f", ShipTransSpeed);

	/*if (XtremeMath::EuclideanNorm(ShipPos - PlayerTankManager::getPlayerTankPos()) < 2500) {
		if (!Collidable::isRegistered()) {
			SubmitCollisionRegistration();
		}
	}
	else if (Collidable::isRegistered()) {
		SubmitCollisionDeregistration();
	}*/
}

void RushTank::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	pGOTurr->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void RushTank::SceneEntry() {
	//DebugMsg::out("SceneEntry: RushTank\n");
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, (float)(rand() % 4) + 1.0f);
	
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_1) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 1.0f);
	lives = 3;
}

void RushTank::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_1) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
	RushTankFactory::RecycleRushTank(this);
}

void RushTank::Collision(PlayerTank*) {
	//DebugMsg::out("Collision RushTank with PlayerTank\n");
}

void RushTank::Collision(PlayerBullet*) {
	//DebugMsg::out("Collision RushTank with PlayerBullet\n");
	--lives;
	if (lives <= 0) {
		GameObject::SubmitExit();
		SoundPlayer::playSound("Explosion", ShipPos);

	}
	

	
}

void RushTank::Alarm0() {
	//if (getRegState() == GameObject::RegistrationState::CURRENTLY_REGISTERED) {
		//BulletFactory::CreateBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));
	if (XtremeMath::EuclideanNorm(ShipPos - PlayerTankManager::getPlayerTankPos()) < 1000) {
		EnemyBulletFactory::CreateEnemyBullet(TurrRot, TurrScale, TurrPos + Vect(0, ShipPos[y], 0));
		SoundPlayer::playSound("BAM", ShipPos);
	}
	if (getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);
	//else DebugMsg::out("Failed to submit registration.");
//}


}