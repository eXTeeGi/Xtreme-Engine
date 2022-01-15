#include "WorldPlane.h"
#include "..//Game/SceneGameTest.h"
#include "..//Game/SceneTutorial.h"

WorldPlane::WorldPlane() {
	pGObjFT = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), ShaderManager::Get("TextureFlat"), TextureManager::Get("GridTex"));
	pGObjCol = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"), ShaderManager::Get("ColorNoTexture"));

	// Creating matrices for in-world placement
	Matrix world;

	// Axis and Plane
	world = Matrix(IDENTITY);
	pGObjCol->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400);
	pGObjFT->SetWorld(world);

	//Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	/*Inputable::SceneRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_PRESS);
	Inputable::SceneRegistration(AZUL_KEY::KEY_M, KeyboardEventManager::KEY_PRESS);*/
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ENTER, KeyboardEventManager::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_M, KeyboardEventManager::KEY_PRESS);

	//SetCollidableGroup<WorldPlane>();
	//SubmitCollisionRegistration();
}

WorldPlane::~WorldPlane() {
	delete pGObjFT;
	delete pGObjCol;
}

void WorldPlane::Draw() {
	//pGObjFT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	//pGObjCol->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void WorldPlane::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("<SPACE> pressed\n", k);
		break;
	case AZUL_KEY::KEY_M:
		DebugMsg::out("<M> pressed\n", k);
		break;
	case AZUL_KEY::KEY_ENTER:
		DebugMsg::out("<ENTER> pressed\n", k);
		SceneManager::SetNextScene(new SceneTutorial());
		break;
	default:
		DebugMsg::out("ERROR: Key %i unprocessed\n", k);
	}
}

void WorldPlane::KeyReleased(AZUL_KEY k) {
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("<SPACE> released\n", k);

		break;
	
	default:
		break;
	}
}