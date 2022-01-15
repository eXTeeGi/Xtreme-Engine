#include "WorldTerrain.h"
#include "..//Game/SceneGameTest.h"

WorldTerrain::WorldTerrain() {
	pTerrain = new Model(100, 500, 500);  // plane 1000x1000 unit with 100 texture repeats along U and 100 texture repeats along v

	pGObjFT = new GraphicsObject_TextureFlat(pTerrain, ShaderManager::Get("TextureFlat"), TextureManager::Get("Grass"));

	//pGObjFT = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), ShaderManager::Get("TextureFlat"), TextureManager::Get("Grass"));
	pGObjCol = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"), ShaderManager::Get("ColorNoTexture"));

	// Creating matrices for in-world placement
	Matrix world;

	// Axis and Plane
	world = Matrix(IDENTITY);
	pGObjCol->SetWorld(world);
	world = Matrix(SCALE, 4000, 4000, 4000);
	pGObjFT->SetWorld(world);

	//Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SetCollidableGroup<WorldTerrain>();
	SubmitCollisionRegistration();
}

WorldTerrain::~WorldTerrain() {
	delete pGObjFT;
	delete pGObjCol;
	delete pTerrain;
}

void WorldTerrain::Draw() {
	pGObjFT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	pGObjCol->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}