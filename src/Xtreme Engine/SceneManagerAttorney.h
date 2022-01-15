#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
	friend class XtremeEngine;
public:
	static void Delete() { SceneManager::Delete(); };

	//static void InitStartScene() { Instance().privInitStartScene(); }
	static void InitStartScene() { SceneManager::InitStartScene(); };

	//static void ChangeScene(Scene* arg) { Instance().privChangeScene(arg); }
	static void ChangeScene(Scene* arg) { SceneManager::ChangeScene(arg); };

	//static void Draw() { Instance().privDraw(); }
	static void Draw() { SceneManager::Draw(); };

	//static void Draw2D() { Instance().privDraw2D(); }
	//static void Draw2D() { SceneManager::Draw2D(); };

	//static void Update() { Instance().privUpdate(); }
	static void Update() { SceneManager::Update(); };
};


#endif _SceneManagerAttorney