#include "PlayerTank.h"
#include "PlayerTankCamera.h"
#include "FPSCamera.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "../Demo/Bullet.h"
#include "PlayerTurret.h"
#include "PlayerTankManager.h"
#include "../Xtreme Engine///ScreenLog.h"
#include "..//Xtreme Engine/////XtremeMath.h"
#include "Die.h"
#include "Rock.h"
#include "Headlines.h"
#include "PowerupManager.h"
#include "..//Xtreme Engine///SoundPlayer.h"

PlayerTank::PlayerTank() {

	
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Tank"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankGreen"), Color, LightPos);

	// Creating matrices for in-world placement
	Matrix world;

	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 0, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	//Camera
	//cam = new PlayerTankCamera(ShipPos);
	//cam = new PlayerTankCamera(ShipPos, ShipRot, Vect(0, 1, 0), Vect(0, 0, 1));
	//SceneManager::GetCurrentScene()->getCamMan()->SetCurrentCamera(cam->getCameraPtr());

	GameObject::SubmitEntry();

	SetColliderModel(pGO->getModel(), VolumeType::OBB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<PlayerTank>();
	//SubmitCollisionRegistration();

	//Turret
	turret = new PlayerTurret();
	turret->respawn();
}



PlayerTank::~PlayerTank() {
	delete pGO;
	delete turret;
}

void PlayerTank::Update() {
	if (beingAbducted) {
		ShipPos[y] += 0.5f;
		beingAbducted = false;
	}
	else {
		if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT) && !Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE)) {
			// Ship translation movement (not using time-based values for simplicity)
			if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
			{
				//ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
				if (ShipTransSpeed < maxSpeed * speedBoosted) ShipTransSpeed += 0.05f * speedBoosted;
				else if (ShipTransSpeed > maxSpeed * speedBoosted) ShipTransSpeed = maxSpeed * speedBoosted;
			}
			else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
			{
				//ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
				if (ShipTransSpeed > -maxSpeed * speedBoosted) ShipTransSpeed -= 0.05f * speedBoosted;
				else if (ShipTransSpeed < -maxSpeed * speedBoosted) ShipTransSpeed = -maxSpeed * speedBoosted;
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
		if (!Keyboard::GetKeyState(KEY_SPACE)) {
			if (ShipPos[y] > 0) ShipPos[y] -= 1.0f;
			else ShipPos[y] = 0;
		}
		
	}
	

	//bounds
	if (XtremeMath::EuclideanNorm(ShipPos - Vect(0, 0, 0)) > 3000) /*ShipRot *= Matrix(ROT_Y, MATH_PI);*/ {
		// ACTUALLY GOOD
		ShipPos += (Vect(0,ShipPos[Y],0) - ShipPos).getNorm() * maxSpeed * (float)speedBoosted;
	}

	

	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);



	//Turret
	turret->MyUpdate(ShipPos);

	this->UpdateCollisionData(world);



	

}

void PlayerTank::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

	
}

void PlayerTank::SceneEntry() {
	Matrix world;
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 0, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	turret->SubmitEntry();
	

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_RELEASE);
	Collidable::SubmitCollisionRegistration();
	SceneManager::GetCurrentScene()->getCamMan()->SetCurrentCamera(turret->getCam()->getCameraPtr());

	turret->respawn();
}

void PlayerTank::SceneExit() {
	turret->SubmitExit();
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_RELEASE);
	Collidable::SubmitCollisionDeregistration();
}

void PlayerTank::KeyPressed(AZUL_KEY k)
{
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) {
		switch (k)
		{
		case AZUL_KEY::KEY_SPACE:
			SceneManager::GetCurrentScene()->getCamMan()->SetCurrentCamera(turret->getFPSCam()->getCameraPtr());
			turret->getFPSCam()->reorient(turret->getCam()->getRot());
			break;

		default:
			DebugMsg::out("ERROR: Key %i unprocessed\n", k);
		}
	}
}

void PlayerTank::KeyReleased(AZUL_KEY k)
{
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) {
		switch (k)
		{
		case AZUL_KEY::KEY_SPACE:
			SceneManager::GetCurrentScene()->getCamMan()->SetCurrentCamera(turret->getCam()->getCameraPtr());

			break;

		default:
			DebugMsg::out("ERROR: Key %i unprocessed\n", k);
		}
	}
}

void PlayerTank::Collision(EnemyTank*) {
	//DebugMsg::out("Collision PlayerTank with EnemyTank\n");
	//PlayerTankManager::respawnPlayer();
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();
}

void PlayerTank::Collision(UFO*) {
	//DebugMsg::out("Collision PlayerTank with EnemyTank\n");
	//PlayerTankManager::respawnPlayer();
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();
}

void PlayerTank::Collision(RushTank*) {
	//DebugMsg::out("Collision PlayerTank with RushTank\n");
	//PlayerTankManager::respawnPlayer();
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();
}

void PlayerTank::Collision(TrainingTarget*) {
	//DebugMsg::out("Collision PlayerTank with RushTank\n");
	//PlayerTankManager::respawnPlayer();
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();
}

void PlayerTank::Collision(BossTank*) {
	//DebugMsg::out("Collision PlayerTank with RushTank\n");
	//PlayerTankManager::respawnPlayer();
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();
}

void PlayerTank::Collision(EnemyBullet*) {
	//DebugMsg::out("Collision PlayerTank with EnemyBullet\n");
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) PlayerTankManager::damagePlayer();

}

void PlayerTank::Collision(AmmoPickup*) {
	turret->addAmmo(20);
	SoundPlayer::playSound("Reload");
	Headlines::add("Ammo Reloaded!");
}

void PlayerTank::Collision(Powerup*) {
	
}

void PlayerTank::Collision(Die* ) {
	/*Vect otherPos = other->getPos();


	
	otherPos[Y] = ShipPos[Y];
	ShipPos += (ShipPos - otherPos).getNorm() * maxSpeed;

	
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);




	turret->MyUpdate(ShipPos);

	this->UpdateCollisionData(world);*/
}

void PlayerTank::Collision(Rock* other) {
	Vect otherPos = other->getPos();



	otherPos[Y] = ShipPos[Y];
	ShipPos += (ShipPos - otherPos).getNorm() * maxSpeed * (float)speedBoosted;


	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);




	turret->MyUpdate(ShipPos);

	this->UpdateCollisionData(world);
}

void PlayerTank::respawn() {
	Matrix world;
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 0, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	ShipTransSpeed = 0.0f;
	turret->respawn();
}

bool PlayerTank::isAlive() {
	if (GameObject::getRegState() == GameObject::RegistrationState::CURRENTLY_REGISTERED) return true;
	else return false;
}

void PlayerTank::powerupSpeedBoost() {
	if (Alarmable::getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_DEREGISTERED) {
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.0f);
		speedBoosted = 2;
	}
	
}

void PlayerTank::Alarm0() {
	speedBoosted = 1;
}

void PlayerTank::abduct() {
	beingAbducted = true;
}