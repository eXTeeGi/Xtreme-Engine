#ifndef _Headlines
#define _Headlines

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <list>
#include "..//Xtreme Engine/SpriteFont.h"

class Headlines : public GameObject
{
public:
	static Headlines* ptrinstance;

	static void add(std::string message) { Instance().privAdd(message); };
	static void Terminate(); /*{ Instance().privTerminate(); }*/

	static void Init() { Instance().privInit(); }
	static void endScene() { Instance().privEndScene(); }

private:
	Headlines();
	~Headlines() {};

	static Headlines& Instance() {
		if (!ptrinstance)
			ptrinstance = new Headlines;
		return *ptrinstance;
	}

	void privInit();
	void privEndScene();

	void privAdd(std::string message);
	//void privTerminate();

	//void Alarm0();
	void Draw2D();

	std::list<std::string> SQ;
	SpriteFont* Font;
	bool IsDraw;
	int Counter;
};

#endif _Headlines