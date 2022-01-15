#include "Visualizer.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "CollisionVolume.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeBSphere.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "VisualizerDrawBSphereCommand.h"
#include "VisualizerDrawAABBCommand.h"
#include "VisualizerDrawOBBCommand.h"
#include "VisualizerBroker.h"
#include "VisualizerDrawBSphereCommandFactory.h"
#include "VisualizerDrawAABBCommandFactory.h"
#include "VisualizerDrawOBBCommandFactory.h"

Visualizer* Visualizer::ptrinstance;

Visualizer::Visualizer() {
	//DEFAULT_COLOR = Vect(0, 0, 1, 1);
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Box"), ShaderManager::Get("ColorConstant"), Blue);
	vBrok = new VisualizerBroker();
}

void Visualizer::Delete() {
	Instance().privDelete();

	delete ptrinstance;
	ptrinstance = nullptr;
}

void Visualizer::privDelete() {
	delete WFUnitSphere;
	delete WFUnitBox;
	delete vBrok;

	
}

void Visualizer::ShowCollisionVolume(const CollisionVolume& S, const Vect& col) {
	Instance().privShowCollisionVolume(S, col);
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col) {
	Instance().privShowBSphere(S, col);
}

void Visualizer::ShowBSphere(Vect& S, const Vect& col) {
	Instance().privShowBSphere(S, col);
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& S, const Vect& col) {
	Instance().privShowAABB(S, col);
}

void Visualizer::ShowAABB(Vect& min, Vect& max, const Vect& col/* = DEFAULT_COLOR*/) {
	Instance().privShowAABB(min,max,col);
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& S, const Vect& col) {
	Instance().privShowOBB(S, col);
}

void Visualizer::privShowCollisionVolume(const CollisionVolume& S, const Vect& col) {
	S.DebugView(col);
}

void Visualizer::privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col) {
	Matrix SRT = Matrix(SCALE, S.GetRadius(), S.GetRadius(), S.GetRadius()) * Matrix(TRANS, S.GetCenter());
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) vBrok->addCommand(VisualizerDrawBSphereCommandFactory::CreateVisualizerDrawBSphereCommand(SRT,col));
}

void Visualizer::privShowBSphere(Vect& S, const Vect& col) {
	Matrix SRT = Matrix(SCALE, 1,1,1) * Matrix(TRANS, S);
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) vBrok->addCommand(VisualizerDrawBSphereCommandFactory::CreateVisualizerDrawBSphereCommand(SRT, col));
}

void Visualizer::privShowAABB(const CollisionVolumeAABB& S, const Vect& col) {
	Matrix SRT = Matrix(SCALE, S.getCornerMax().X() - S.getCornerMin().X(), S.getCornerMax().Y() - S.getCornerMin().Y(), S.getCornerMax().Z() - S.getCornerMin().Z()) * Matrix(TRANS, { (S.getCornerMax().X() + S.getCornerMin().X())/2, (S.getCornerMax().Y() + S.getCornerMin().Y())/2, (S.getCornerMax().Z() + S.getCornerMin().Z())/2 });
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) vBrok->addCommand(VisualizerDrawAABBCommandFactory::CreateVisualizerDrawAABBCommand(SRT, col));
}

void Visualizer::privShowAABB(Vect& min, Vect& max, const Vect& col) {
	Matrix SRT = Matrix(SCALE, max.X() - min.X(), max.Y() - min.Y(), max.Z() - min.Z()) * Matrix(TRANS, { (max.X() + min.X()) / 2, (max.Y() + min.Y()) / 2, (max.Z() + min.Z()) / 2 });

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) vBrok->addCommand(VisualizerDrawAABBCommandFactory::CreateVisualizerDrawAABBCommand(SRT, col));
}

void Visualizer::privShowOBB(const CollisionVolumeOBB& S, const Vect& col) {
	//Matrix SRT = S.getW().getInv();
	Matrix SRT = Matrix(SCALE, S.getCornerMax().X() - S.getCornerMin().X(), S.getCornerMax().Y() - S.getCornerMin().Y(), S.getCornerMax().Z() - S.getCornerMin().Z()) * Matrix(TRANS, { (S.getCornerMax().X() + S.getCornerMin().X()) / 2, (S.getCornerMax().Y() + S.getCornerMin().Y()) / 2, (S.getCornerMax().Z() + S.getCornerMin().Z()) / 2 });
	SRT *= S.getW();
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) vBrok->addCommand(VisualizerDrawOBBCommandFactory::CreateVisualizerDrawOBBCommand(SRT, col));
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col) {
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->SetColor(col);
	WFUnitSphere->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Visualizer::privRenderAABB(Matrix& S, const Vect& col) {
	WFUnitBox->SetWorld(S);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Visualizer::privRenderOBB(Matrix& S, const Vect& col) {
	WFUnitBox->SetWorld(S);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
}

void Visualizer::VisualizeAll() {
	vBrok->ExecuteCommands();
}