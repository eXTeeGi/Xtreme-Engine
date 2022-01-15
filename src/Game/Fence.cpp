#include "Fence.h"
#include "..//Xtreme Engine/////SceneManager.h"

Fence::Fence() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	//pGOList.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fence"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"), Color, LightPos));
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Fence"), ShaderManager::Get("TextureLight"), TextureManager::Get("TankTan"),Color,LightPos);

	Matrix S = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	//Matrix R = Matrix(IDENTITY);
	Matrix T = Matrix(TRANS, Vect(0, 30, 0));
	Matrix world = S * T;
	pGO->SetWorld(world);

	SubmitDrawRegistration();
}

Fence::~Fence() {
	std::list<GraphicsObject_TextureLight*>::iterator it;
	for (it = pGOList.begin(); it != pGOList.end(); it++) {
		delete (*it);
	}
	
	delete pGO;
}

void Fence::Draw() {
	std::list<GraphicsObject_TextureLight*>::iterator it;
	for (it = pGOList.begin(); it != pGOList.end(); it++) {
		(*it)->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	}

	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Fence::generateFence(int ) {

}