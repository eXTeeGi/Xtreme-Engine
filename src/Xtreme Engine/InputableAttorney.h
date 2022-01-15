#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"
#include "KeyboardEventManager.h"

class InputableAttorney
{
public:

public:
	class Registration
	{
		friend class KeyRegistrationCommand;
		friend class KeyDeregistrationCommand;
	private:
		static void KeyRegistration(Inputable* pMgr, AZUL_KEY k, KeyboardEventManager::EVENT_TYPE ev) { pMgr->SceneRegistration(k, ev); }
		static void KeyDeregistration(Inputable* pMgr, AZUL_KEY k, KeyboardEventManager::EVENT_TYPE ev) { pMgr->SceneDeregistration(k, ev); }
	};
};


#endif _InputableAttorney