#include "BulletBase.h"
#include "..//Xtreme Engine///Visualizer.h"
#include "..//Xtreme Engine///XtremeMath.h"
#include "PlayerTankManager.h"

BulletBase::BulletBase() {

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Color(0.0f, 0.0f, 0.0f, 1.0f);
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




BulletBase::~BulletBase() {
	delete pGObjLT;
}

void BulletBase::Update() {

	ShipPos += Vect(0, 0, 3) * ShipRot * ShipTransSpeed;
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);

	if (XtremeMath::EuclideanNorm(ShipPos - PlayerTankManager::getPlayerTankPos()) > 3000) this->SubmitExit();

	UpdateCollisionData(pGObjLT->getWorld());

}

void BulletBase::Draw() {
	pGObjLT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void BulletBase::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
}

