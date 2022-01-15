#include "ScreenLog.h"

#include "SpriteFont.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"

ScreenLog* ScreenLog::ptrinstance;
char ScreenLog::DebugBuff[256];

ScreenLog::ScreenLog() {
	font = SpriteFontManager::Get("Sans18");
}

void ScreenLog::Add(char* A, ...) {
	va_list args;

	va_start(args, A);
	vsprintf_s(DebugBuff, A, args);
	va_end(args);

	std::string s(DebugBuff);
	Instance().messages.push_back(s);

}

void ScreenLog::Render() {
	Instance().privRender();
}

void ScreenLog::Delete() {
	Instance().privDelete();
}

void ScreenLog::privRender() {
	int x = anchorX;
	int y = anchorY;

	std::list<std::string>::iterator it;
	for (it = messages.begin(); it != messages.end(); it++) {
		SpriteString tmpSS = SpriteString(font, (*it), x, y);
		tmpSS.Render();
		y += tmpSS.GetHeight();
	}

	messages.clear();
	//x; y;
}

void ScreenLog::privDelete() {
	delete ptrinstance;
	ptrinstance = nullptr;
}
