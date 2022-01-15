#ifndef _HUD
#define _HUD

#include "AzulCore.h"
#include "..//Xtreme Engine/GameObject.h"

class SpriteString;
class XtremeSprite;

class HUD : public GameObject
{
public:
	static HUD* ptrinstance;

	static void updateLives(int numLives) { Instance().privUpdateLives(numLives); };
	static void updateWave(int numWave) { Instance().privUpdateWave(numWave); };
	static void updateAmmo(int numAmmo) { Instance().privUpdateAmmo(numAmmo); };
	static void Delete();

	//timer
	static void restartTimer() { Instance().privRestartTimer(); }
	static void endTimer() { Instance().privEndTimer(); }

	static void Init() { Instance().privInit(); }
	static void endScene() { Instance().privEndScene(); }

private:
	static HUD& Instance() {
		if (!ptrinstance)
			ptrinstance = new HUD;
		return *ptrinstance;
	}

	HUD();
	~HUD();

	void privInit();
	void privEndScene();

	void privRender();
	void privUpdateLives(int i);
	void privUpdateWave(int i);
	void privUpdateAmmo(int i);
	//void privDelete();

	//timer
	void privRestartTimer();
	void privEndTimer();

	virtual void Draw2D() override;
	virtual void Update() override;
	virtual void Alarm0();
	virtual void Alarm1();

	int lives;
	int wave;
	int ammo;
	bool Endgame;

	XtremeSprite* heart1;
	XtremeSprite* heart2;
	XtremeSprite* heart3;
	XtremeSprite* crosshair;
	SpriteString* SSwave;
	SpriteString* SSammo;
	SpriteString* SSendgame;

	//timer
	float startTime;
	float timer;
	bool renderTimer;
	SpriteString* SStimer;
};

#endif _HUD