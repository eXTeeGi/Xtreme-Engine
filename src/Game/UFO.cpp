#include "UFO.h"

#include "../Xtreme Engine/XtremeMath.h"
#include "../Xtreme Engine/ScreenLog.h"
#include "PlayerTankManager.h"
#include "UFOFactory.h"
#include "..//Xtreme Engine///SoundPlayer.h"

UFO::UFO(Vect arg) {
	float r, g, b;
	r = ((float)(rand() % 10) / 10);
	g = ((float)(rand() % 10) / 10);
	b = ((float)(rand() % 10) / 10);
	Vect Color(r, g, b, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("UFO"), ShaderManager::Get("TextureLight"), TextureManager::Get("ufo"), Color, LightPos);



	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipRot *= Matrix(ROT_Z, MATH_4PI8);
	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);

	SetColliderModel(pGO->getModel(), VolumeType::AABB);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<UFO>();
}

void UFO::Initialize(Vect arg) {
	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ShipRot.set(IDENTITY);
	ShipRot *= Matrix(ROT_X, MATH_4PI8);

	ShipPos.set(arg);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGO->SetWorld(world);


	GameObject::SubmitEntry();


	//SubmitCollisionRegistration();

}

UFO::~UFO() {
	delete pGO;
}

void UFO::Update() {
	Vect ShipPosY = ShipPos;
	ShipPosY[y] = PlayerTankManager::getPlayerTankPos().Y();
	if (XtremeMath::EuclideanNorm(ShipPosY - PlayerTankManager::getPlayerTankPos()) < 500) {
		if (XtremeMath::EuclideanNorm(ShipPosY - PlayerTankManager::getPlayerTankPos()) < 100) PlayerTankManager::abduct();
		if (ShipPos.X() > PlayerTankManager::getPlayerTankPos().X()) xDir = -1;
		if (ShipPos.X() < PlayerTankManager::getPlayerTankPos().X()) xDir = 1;
		if (ShipPos.Z() > PlayerTankManager::getPlayerTankPos().Z()) zDir = -1;
		if (ShipPos.Z() < PlayerTankManager::getPlayerTankPos().Z()) zDir = 1;
	}
	else {
		if (ShipPos.X() > 3000) xDir = -1;
		if (ShipPos.X() < -3000) xDir = 1;
		if (ShipPos.Z() > 3000) zDir = -1;
		if (ShipPos.Z() < -3000) zDir = 1;
	}

	if (XtremeMath::EuclideanNorm(ShipPosY - PlayerTankManager::getPlayerTankPos()) >= 5) {
		ShipPos[x] += xDir * ShipTransSpeed;
		ShipPos[z] += zDir * ShipTransSpeed;
	}

	

	//ShipPos += Vect(0, 0, 1) * ShipRot * (ShipTransSpeed * WorS);
	//ShipRot *= Matrix(ROT_Y, -(ShipRotAng * AorD));
	//bounds


	ShipRot *= Matrix(ROT_Y, MATH_4PI8 / 100);


	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	 pGO->SetWorld(world);

	//turret->MyUpdate(ShipPos);

	UpdateCollisionData(pGO->getWorld());


}

void UFO::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void UFO::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	SoundPlayer::playSound("Sonar", ShipPos);
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 3.529f);

}

void UFO::SceneExit() {
	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	if (Alarmable::getAlarmRegState(AlarmableManager::ALARM_ID::ALARM_0) == Alarmable::RegistrationState::CURRENTLY_REGISTERED) SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	UFOFactory::RecycleUFO(this);
}

void UFO::Collision(PlayerBullet*) {
	GameObject::SubmitExit();
	SoundPlayer::playSound("Explosion", ShipPos);

}

void UFO::Alarm0() {
	SoundPlayer::playSound("Sonar", ShipPos);
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 3.529f);
}