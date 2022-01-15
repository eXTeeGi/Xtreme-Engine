#include "AmmoPickup.h"
#include "AmmoPickupFactory.h"
#include "..//Xtreme Engine/XtremeColors.h"

AmmoPickup::AmmoPickup() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("AmmoCrate" ),Color, LightPos);
}

void AmmoPickup::Initialize(Vect arg) {
	Matrix world;
	Scale.set(SCALE, 10.0f, 10.0f, 10.0f);
	Rot.set(IDENTITY);
	Pos = arg;
	Pos[Y] = 5;
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGO->SetWorld(world);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	SetColliderModel(pGO->getModel(), VolumeType::BSPHERE);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<AmmoPickup>();
	SubmitCollisionRegistration();

	SubmitEntry();
}

AmmoPickup::AmmoPickup(float argX, float argZ) {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Box"), ShaderManager::Get("TextureLight"), TextureManager::Get("AmmoCrate"), Color, LightPos);


	Matrix world;
	Scale.set(SCALE, 10.0f, 10.0f, 10.0f);
	Rot.set(IDENTITY);
	Pos.set(argX, 10, argZ);
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGO->SetWorld(world);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	
	SetColliderModel(pGO->getModel(), VolumeType::BSPHERE);
	UpdateCollisionData(pGO->getWorld());
	SetCollidableGroup<AmmoPickup>();
	SubmitCollisionRegistration();

	SubmitEntry();
}

AmmoPickup::~AmmoPickup() {
	delete pGO;
}

void AmmoPickup::Update() {
}

void AmmoPickup::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void AmmoPickup::Collision(PlayerTank*) {
	SubmitExit();
}

void AmmoPickup::SceneExit() {
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	AmmoPickupFactory::RecycleAmmoPickup(this);
}