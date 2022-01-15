#include "Cottage.h"

Cottage::Cottage() {
	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(ModelManager::Get("Cottage"), ShaderManager::Get("TextureLight"), TextureManager::Get("Cottage"), Color, LightPos);

	Matrix S = Matrix(SCALE, 300.0f, 300.0f, 300.0f);
	//Matrix R = Matrix(IDENTITY);
	Matrix T = Matrix(TRANS, Vect(0, 0, -5000));
	Matrix world = S * T;
	pGO->SetWorld(world);

	SubmitDrawRegistration();
}

Cottage::~Cottage() {
	delete pGO;
}

void Cottage::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}