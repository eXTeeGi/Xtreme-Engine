#include "XtremeSprite.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"


XtremeSprite::~XtremeSprite() {
	delete pGOSprite;
	delete defRect;
}

XtremeSprite::XtremeSprite(string arg) {
	defRect = new Rect(500, 500, 100.0f, 100.0f);
	re = defRect;
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("Sprite"),ShaderManager::Get("Sprite"),ImageManager::Get(arg), defRect /*Model, shader, image, rect*/);
	Matrix S = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix R = Matrix(ROT_Z, 0.0f);
	Matrix T = Matrix(TRANS, pGOSprite->origPosX,
		pGOSprite->origPosY, 0.0f);

	Matrix world = S*R*T;
	pGOSprite->SetWorld(world);

	centerX = 0;
	centerY = 0;
	posZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	angle = 0.0f;
}

XtremeSprite::XtremeSprite(string arg, Rect* r) {
	defRect = new Rect(500, 500, 100.0f, 100.0f);
	re = r;
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("Sprite"), ShaderManager::Get("Sprite"), ImageManager::Get(arg), r /*Model, shader, image, rect*/);
	Matrix S = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix R = Matrix(ROT_Z, 0.0f);
	Matrix T = Matrix(TRANS, pGOSprite->origPosX,
		pGOSprite->origPosY, 0.0f);

	Matrix world = S * R * T;
	pGOSprite->SetWorld(world);

	centerX = 0;
	centerY = 0;
	posZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	angle = 0.0f;
}

float XtremeSprite::GetAngle() {
	return angle;
}

void XtremeSprite::Render(Camera* arg) {
	pGOSprite->Render(arg);
}

void XtremeSprite::Render() {
	pGOSprite->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrent2DCamera());
}

void XtremeSprite::SetAngle(float arg) {
	angle = arg;

	setWorld();
}

void XtremeSprite::setWorld() {
	Matrix offset = Matrix(TRANS, -centerX, -centerY, 0.0f);
	Matrix S = Matrix(SCALE, scaleX, scaleY, 1.0f);
	Matrix R = Matrix(ROT_Z, angle);
	Matrix T = Matrix(TRANS, pGOSprite->origPosX, pGOSprite->origPosY, posZ);
	Matrix world = S * offset * R * T;
	pGOSprite->SetWorld(world);
}

void XtremeSprite::SetCenter(float argX, float argY) {
	centerX = argX;
	centerY = argY;
}

void XtremeSprite::SetPosition(float argX, float argY) {
	pGOSprite->origPosX = argX;
	pGOSprite->origPosY = argY;

	setWorld();
}

void XtremeSprite::SetScaleFactor(float argX, float argY) {
	scaleX = argX;
	scaleY = argY;

	setWorld();
}

void XtremeSprite::SetScalePixel(float argX, float argY) {
	//scaleX = argX / pGOSprite->pImage->pText->getWidth();
	//scaleY = argY / pGOSprite->pImage->pText->getHeight();

	scaleX = argX / re->width;
	scaleY = argY / re->height;

	setWorld();
}

void XtremeSprite::SetLayer(float arg) {
	posZ = arg;

	setWorld();
}

float XtremeSprite::getWidth() {
	return re->width;
}

float XtremeSprite::getHeight() {
	return re->height;
}