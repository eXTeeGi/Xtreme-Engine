#include "PlayerTurret.h"
#include "PlayerTankCamera.h"
#include "FPSCamera.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "PlayerBulletFactory.h"
#include "../Demo/Bullet.h"
#include "../Xtreme Engine/ScreenLog.h"
#include "..//Xtreme Engine///SoundPlayer.h"
#include "HUD.h"

PlayerTurret::PlayerTurret() {

	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Turret"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankGreen"), Color, LightPos);

	// Creating matrices for in-world placement
	Matrix world;

	// SpaceTurr
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	world = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGO->SetWorld(world);

	//Camera
	cam = new PlayerTankCamera(TurrPos);
	fpscam = new FPSCamera(TurrPos);
	//cam = new PlayerTurretCamera(TurrPos, TurrRot, Vect(0, 1, 0), Vect(0, 0, 1));
	//SceneManager::GetCurrentScene()->getCamMan()->SetCurrentCamera(cam->getCameraPtr());

	//GameObject::SubmitEntry();
}



PlayerTurret::~PlayerTurret() {
	delete pGO;
	delete cam;
	delete fpscam;
}

void PlayerTurret::Update() {
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
	Matrix world = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGO->SetWorld(world);

	//Camera
	cam->updateTankPos(TurrPos + Vect(0, 40, 0), TurrRot);
	fpscam->updateTankPos(TurrPos + Vect(0,20,0));



	//FMOD
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE)) SoundPlayer::setListenerPos(TurrPos, TurrRot.get(ROW_2), TurrRot.get(ROW_1));
	else SoundPlayer::setListenerPos(fpscam->getPos(), fpscam->getRot().get(ROW_2), fpscam->getRot().get(ROW_1));

}

void PlayerTurret::Draw() {
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE)) pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void PlayerTurret::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyboardEventManager::KEY_PRESS);
	canShoot = true;
	HUD::updateAmmo(ammo);

}

void PlayerTurret::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, KeyboardEventManager::KEY_PRESS);
}

void PlayerTurret::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ARROW_UP:
		if (canShoot == true && ammo > 0) {
			if (!Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE)) PlayerBulletFactory::CreatePlayerBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));
			else PlayerBulletFactory::CreatePlayerBullet(fpscam->getRot(), TurrScale, fpscam->getPos() + Vect(0, 20, 0));
			
			SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f);
			--ammo;
			HUD::updateAmmo(ammo);
			canShoot = false;
			SoundPlayer::playSound("BAM");
		}
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		//SoundPlayer::playSound("Cave");

	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}

void PlayerTurret::MyUpdate(Vect arg) {
	TurrPos = arg + Vect(0, 0, 0);
}

void PlayerTurret::Alarm0() {
	canShoot = true;
}

void PlayerTurret::respawn() {
	Matrix world;
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	world = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGO->SetWorld(world);
	ammo = 100;
}

void PlayerTurret::addAmmo(int arg) {
	ammo += arg;
	HUD::updateAmmo(ammo);
}