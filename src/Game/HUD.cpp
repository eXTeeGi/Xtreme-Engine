#include "HUD.h"

#include "..//Xtreme Engine///XtremeSprite.h"
#include "..//Xtreme Engine///XtremeEngine.h"
#include "..//Xtreme Engine///SpriteString.h"
#include "..//Xtreme Engine///SpriteFontManager.h"
#include "..//Xtreme Engine/TimeManager.h"
#include "..//Xtreme Engine/XtremeMath.h"

HUD* HUD::ptrinstance;

HUD::HUD() {
	heart1 = new XtremeSprite("Heart");
	heart1->SetAngle(0);
	heart1->SetScaleFactor(0.5f, 0.5f);
	heart1->SetPosition(32.0f, XtremeEngine::GetHeight() - 32.0f);
	heart1->SetCenter(0, 0);
	heart1->SetLayer(0.3f);

	heart2 = new XtremeSprite("Heart");
	heart2->SetAngle(0);
	heart2->SetScaleFactor(0.5f, 0.5f);
	heart2->SetPosition(32.0f * 3, XtremeEngine::GetHeight() - 32.0f);
	heart2->SetCenter(0, 0);
	heart2->SetLayer(0.3f);

	heart3 = new XtremeSprite("Heart");
	heart3->SetAngle(0);
	heart3->SetScaleFactor(0.5f, 0.5f);
	heart3->SetPosition(32.0f * 5, XtremeEngine::GetHeight() - 32.0f);
	heart3->SetCenter(0, 0);
	heart3->SetLayer(0.3f);

	crosshair = new XtremeSprite("Crosshair");
	crosshair->SetAngle(0);
	crosshair->SetScaleFactor(0.05f, 0.05f);
	crosshair->SetPosition((float)(XtremeEngine::GetWidth() / 2), (float)(XtremeEngine::GetHeight() / 2));
	crosshair->SetCenter(0, 0);
	crosshair->SetLayer(0.3f);

	SSwave = new SpriteString(SpriteFontManager::Get("Sans18"), "WAVE_UNSET", 16, XtremeEngine::GetHeight() - (32 * 3));
	SSammo = new SpriteString(SpriteFontManager::Get("Sans18"), "AMMO_UNSET", 16, XtremeEngine::GetHeight() - (32 * 4));
	SStimer = new SpriteString(SpriteFontManager::Get("Sans18"), "TIMER_UNSET", 16, XtremeEngine::GetHeight() - (32 * 5));
	SSendgame = new SpriteString(SpriteFontManager::Get("Sans30"), "YOU WIN!!", XtremeEngine::GetWidth() / 2, XtremeEngine::GetHeight() / 2);

	Endgame = false;
	renderTimer = true;
	timer = 0.0f;
	ammo = 100;
	lives = 3;
	wave = -1;
	
}

void HUD::privInit() {
	SubmitDrawRegistration();
	SubmitUpdateRegistration();
}

void HUD::privEndScene() {
	SubmitDrawDeregistration();
	SubmitUpdateDeregistration();
}

void HUD::privRender() {
	if (lives >= 1) heart1->Render();
	if (lives >= 2) heart2->Render();
	if (lives >= 3) heart3->Render();
	if (Endgame) SSendgame->Render();
	if (Keyboard::GetKeyState(KEY_SPACE)) crosshair->Render();
	SSammo->Render();
	SSwave->Render();
	if (renderTimer) SStimer->Render();
}

void HUD::Draw2D() {
	Instance().privRender();
}

void HUD::privUpdateLives(int arg) {
	lives = arg;
}

void HUD::privUpdateWave(int arg) {
	wave = arg;
	XtremeMath::Clamp(wave, 0, 99);
	SSwave->Set(SpriteFontManager::Get("Sans18"), "Wave: " + std::to_string(wave), 16, XtremeEngine::GetHeight() - (32 * 3));
}

void HUD::Delete() {

	delete ptrinstance;
	ptrinstance = nullptr;
}

HUD::~HUD() {
	delete heart1;
	delete heart2;
	delete heart3;

	delete SStimer;
	delete SSendgame;
	delete SSwave;

	delete SSammo;

	delete crosshair;
}

void HUD::privRestartTimer() {
	startTime = TimeManager::GetTime();
}

void HUD::privUpdateAmmo(int arg) {
	ammo = arg;
	SSammo->Set(SpriteFontManager::Get("Sans18"), "Ammo: " + std::to_string(ammo), 16, XtremeEngine::GetHeight() - (32 * 4));
}

void HUD::Update() {
	if (!Endgame) {
		timer = TimeManager::GetTime() - startTime;
		SStimer->Set(SpriteFontManager::Get("Sans18"), "Time: " + std::to_string((int)timer / 60) + ":" + std::to_string((int)timer % 60), 16, XtremeEngine::GetHeight() - (32 * 5));

	}
	
}

void HUD::privEndTimer() {
	//SubmitUpdateDeregistration();
	
	Endgame = true;
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);
}

void HUD::Alarm0() {
	renderTimer = false;
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 1.0f);
}

void HUD::Alarm1() {
	renderTimer = true;
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);
}