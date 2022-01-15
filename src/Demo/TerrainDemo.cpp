#include "TerrainDemo.h"
#include "..//Xtreme Engine/TerrainObject.h"
#include "..//Xtreme Engine/XtremeColors.h"
#include "Frigate.h"
#include "..//Xtreme Engine/CollisionVolumeBSphere.h"
#include "..//Xtreme Engine/ScreenLog.h"

TerrainDemo::TerrainDemo() {
	//pModel = new TerrainObject("Textures/heightmap.tga", 1000, 50, 1, 1);

	Vect Color(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO = new GraphicsObject_TextureLight(pModel->getModel(), ShaderManager::Get("TextureLight"), TextureManager::Get("HMT"), Color, LightPos);
	pWF = new GraphicsObject_WireframeConstantColor(pModel->getModel(), ShaderManager::Get("ColorConstant"), XtremeColors::Blue); 

	GOFrig = new Frigate();

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
}


TerrainDemo::~TerrainDemo() {
	delete pModel;
	delete GOFrig;
	delete pGO;
	delete pWF;
}


void TerrainDemo::Update() {
	//pModel->visualizeAABBs();
	//pModel->identifyCell(GOFrig->getPos().X(), GOFrig->getPos().Z());
	Vect min, max;
	min[x] = GOFrig->getPos().X() - GOFrig->getBSphere().GetRadius();
	min[y] = GOFrig->getPos().Y() - GOFrig->getBSphere().GetRadius();
	min[z] = GOFrig->getPos().Z() - GOFrig->getBSphere().GetRadius();
	max[x] = GOFrig->getPos().X() + GOFrig->getBSphere().GetRadius();
	max[y] = GOFrig->getPos().Y() + GOFrig->getBSphere().GetRadius();
	max[z] = GOFrig->getPos().Z() + GOFrig->getBSphere().GetRadius();
	//pModel->identifyUnder(min, max);
	//pModel->testCollision(min, max, (Collidable*)GOFrig);
	Vect normal = pModel->getNormal(GOFrig->getPos().X(), GOFrig->getPos().Z());
}

void TerrainDemo::Draw() {
	pGO->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	//pWF->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}