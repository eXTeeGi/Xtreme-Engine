#ifndef _ScreenLog
#define _ScreenLog

#include "AzulCore.h"
#include <list>

class SpriteFont;

class ScreenLog
{
	friend class ScreenLogAttorney;
public:
	static ScreenLog* ptrinstance;

	static void Add(char* A, ...);
	

private:
	static void Render();
	static void Delete();

	static ScreenLog& Instance() {
		if (!ptrinstance)
			ptrinstance = new ScreenLog;
		return *ptrinstance;
	}

	ScreenLog();
	~ScreenLog() {};
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;

	void privRender();
	void privDelete();

	int anchorX = 10;
	int anchorY = 10;
	static char DebugBuff[256];
	SpriteFont* font;
	std::list<std::string> messages;
};

#endif _ScreenLog