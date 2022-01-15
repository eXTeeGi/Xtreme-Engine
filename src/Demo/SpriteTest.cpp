#include "SpriteTest.h"

#include "..//Xtreme Engine///SpriteFontManager.h"
#include "..//Xtreme Engine/////ImageManager.h"

SpriteTest::SpriteTest() {
	

	pGOSprite = new XtremeSprite("Stitch");
	pGOSprite->SetAngle(0);
	pGOSprite->SetScalePixel(500, 500);
	pGOSprite->SetScaleFactor(1.0f, 1.0f);
	//pGOSprite->SetPosition(150, 500);
	pGOSprite->SetCenter(50, 50);
	SubmitDrawRegistration();
	SubmitUpdateRegistration();

	pGOSprite2 = new XtremeSprite("Stitch");
	pGOSprite2->SetAngle(0);
	//pGOSprite->SetScaleFactor(1.0f, 1.0f);
	pGOSprite2->SetScalePixel(500, 500);
	pGOSprite2->SetPosition(150, 500);
	pGOSprite2->SetCenter(50, 50);
	pGOSprite2->SetLayer(0.3f);


	// Spritefont Test
	fonttest = SpriteFontManager::Get("Sans18");
	SStest = new SpriteString(fonttest, "Press Enter to begin Tank Game", 100, 200);
	
}

SpriteTest::~SpriteTest() {
	delete pGOSprite;
	delete pGOSprite2;
	//delete fonttest;
	delete SStest;
}

void SpriteTest::Draw2D() {
	pGOSprite->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrent2DCamera());
	pGOSprite2->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrent2DCamera());
	SStest->Render();
}

void SpriteTest::Update() {
	pGOSprite->SetAngle(pGOSprite->GetAngle() + 0.1f);
	//pixels[3] = Texture::UChartoGLbyte(rand()%255);
}