#include "EnemyTurret.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "../Demo/BulletFactory.h"
#include "../Demo/Bullet.h"
#include "PlayerTankManager.h"

EnemyTurret::EnemyTurret() {

	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Turret"), ShaderManager::Get("ColorConstant"), Color);


	// Creating matrices for in-world placement
	Matrix world;

	// SpaceTurr
	TurrScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	TurrRot.set(IDENTITY);
	TurrPos.set(0, 0, 0);
	world = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGO->SetWorld(world);


	GameObject::SubmitEntry();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);

}



EnemyTurret::~EnemyTurret() {
	delete pGO;
}

void EnemyTurret::Update() {

	TurrRot.set(ROT_ORIENT, PlayerTankManager::getPlayerTankPos() - TurrPos, Vect(0,1,0));


	Matrix world = TurrScale * TurrRot * Matrix(TRANS, TurrPos);
	pGO->SetWorld(world);




}

void EnemyTurret::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void EnemyTurret::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyboardEventManager::KEY_PRESS);

}


void EnemyTurret::MyUpdate(Vect arg) {
	TurrPos = arg + Vect(0, 0, 0);
}

void EnemyTurret::Alarm0() {
	BulletFactory::CreateBullet(TurrRot, TurrScale, TurrPos + Vect(0, 20, 0));

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);

}