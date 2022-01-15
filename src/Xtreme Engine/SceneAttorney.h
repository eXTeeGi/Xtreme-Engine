#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"

class SceneAttorney
{

public:
	class Registration
	{
		friend class Alarmable;
		friend class Updatable;
		friend class Drawable;
		friend class Collidable;
		friend class GameObject;
		friend class Inputable;
	private:
		//Updatable
		//void Register(Updatable*, UpdatableManager::StorageListRef&);
		static void Register(Scene* p, Updatable* a, UpdatableManager::StorageListRef& b) { p->Register(a,b); };
		//void Deregister(UpdatableManager::StorageListRef);
		static void Deregister(Scene* p, UpdatableManager::StorageListRef& a) { p->Deregister(a); };

		////Drawable
		//void Register(Drawable*, DrawableManager::StorageListRef&);
		static void Register(Scene* p, Drawable* a, DrawableManager::StorageListRef& b) { p->Register(a, b); };
		//void Deregister(DrawableManager::StorageListRef);
		static void Deregister(Scene* p, DrawableManager::StorageListRef& a) { p->Deregister(a); };

		////Alarmable
		//void Register(float, Alarmable*, AlarmableManager::ALARM_ID, AlarmableManager::StorageMapRef&);
		static void Register(Scene* p, float a, Alarmable* b, AlarmableManager::ALARM_ID c, AlarmableManager::StorageMapRef& d) { p->Register(a, b, c, d); };
		//void Deregister(AlarmableManager::StorageMapRef&);
		static void Deregister(Scene* p, AlarmableManager::StorageMapRef& a) { p->Deregister(a); };

		////Inputable
		//void Register(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);
		static void Register(Scene* p, Inputable* a, AZUL_KEY b, KeyboardEventManager::EVENT_TYPE c) { p->Register(a, b, c); };
		//void Deregister(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);
		static void Deregister(Scene* p, Inputable* a, AZUL_KEY b, KeyboardEventManager::EVENT_TYPE c) { p->Deregister(a, b, c); };

		//void SubmitCommand(CommandBase* argCmd);
		static void SubmitCommand(Scene* p, CommandBase* a) { p->SubmitCommand(a); };

		
		
	};

public:
	class GameLoop
	{
		friend class SceneManager;
	private:
		//void Update();
		static void Update(Scene* p) { p->Update(); };

		//void Draw();
		static void Draw(Scene* p) { p->Draw(); };

		//void Draw2D();
		//static void Draw2D(Scene* p) { p->Draw2D(); };

		static void CreateGodCam(Scene* p) { p->CreateGodCam(); }

		static void runBroker(Scene* p) { p->runBroker(); }
	};
};


#endif _SceneAttorney