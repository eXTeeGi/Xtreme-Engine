#include "Bullet.h"
#include "BulletFactory.h"

Bullet::Bullet() {

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Color(1.0f, 0.0f, 1.0f, 1.0f);
	pGObjLT = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Bullet"), ShaderManager::Get("ColorConstant"), Color);

	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 0.15f, 0.15f, 0.15f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 20, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);

}

void Bullet::Initialize(Matrix argRot, Matrix argScale, Vect argPos) {

	

	// Creating matrices for in-world placement
	Matrix world;
	ShipRot = argRot;
	ShipPos = argPos;
	world = ShipScale * ShipRot * Matrix(TRANS, argPos);
	pGObjLT->SetWorld(world);

	GameObject::SubmitEntry();
}

void Bullet::Alarm0() {
	GameObject::SubmitExit();
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	//Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	
}

Bullet::~Bullet() {
	delete pGObjLT;
}

void Bullet::Update() {
	
		ShipPos += Vect(0, 0, 3) * ShipRot * ShipTransSpeed;
		Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
		pGObjLT->SetWorld(world);
}

void Bullet::Draw() {
	pGObjLT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Bullet::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.0f);
}

void Bullet::SceneExit() {
	BulletFactory::RecycleBullet(this);
}