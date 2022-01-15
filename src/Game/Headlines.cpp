#include "Headlines.h"
#include "..//Xtreme Engine///XtremeEngine.h"
#include "..//Xtreme Engine///SpriteString.h"
#include "..//Xtreme Engine///SpriteFontManager.h"


Headlines* Headlines::ptrinstance;

Headlines::Headlines() {
	Font = SpriteFontManager::Get("Sans30");
	IsDraw = true;
	Counter = 60 * 3;
}

void Headlines::Terminate() {
	delete ptrinstance;
	ptrinstance = nullptr;
}

void Headlines::privAdd(std::string arg) {
	SQ.push_back(arg);
	Counter = 60 * 3;
	//if (Drawable::getRegState() == Drawable::RegistrationState::CURRENTLY_DEREGISTERED) SubmitDrawRegistration();
}

void Headlines::Draw2D() {
	SpriteString tmpSS;
	if (SQ.size() > 0) {
		tmpSS = SpriteString(Font, SQ.front(), (XtremeEngine::GetWidth() / 2) - (SQ.front().size() * 10), XtremeEngine::GetHeight() / 2);
	}
	else  tmpSS = SpriteString(Font, "", (XtremeEngine::GetWidth() / 2), XtremeEngine::GetHeight() / 2);
	tmpSS.Render();
	
	--Counter;
	
	if (Counter <= 0) {
		if (SQ.size() > 0) SQ.pop_front();
		Counter = 60*3;
	}
}

void Headlines::privInit() {
	SubmitDrawRegistration();
}

void Headlines::privEndScene() {
	SubmitDrawDeregistration();
}