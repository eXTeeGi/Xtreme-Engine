#include "Inputable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "KeyRegistrationCommand.h"
#include "KeyDeregistrationCommand.h"
#include "SceneAttorney.h"

void Inputable::SubmitKeyRegistration(AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	RegistrationData* tmpRD;
	switch (argEv)
	{
	case KeyboardEventManager::KEY_PRESS:
		if (pressMap.find(argKey) == pressMap.end()) {
			tmpRD = new RegistrationData();
			tmpRD->InRegCmd = new KeyRegistrationCommand(this, argKey, argEv);
			tmpRD->InDerCmd = new KeyDeregistrationCommand(this, argKey, argEv);
			pressMap.insert(std::pair<AZUL_KEY, RegistrationData*>(argKey, tmpRD));
		}
		else tmpRD = pressMap.find(argKey)->second;

		assert(tmpRD->RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
		//SceneManager::GetCurrentScene()->SubmitCommand(tmpRD->InRegCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), tmpRD->InRegCmd);
		tmpRD->RegStateCurr = RegistrationState::PENDING_REGISTRATION;

		break;
	case KeyboardEventManager::KEY_RELEASE:
		if (releaseMap.find(argKey) == releaseMap.end()) {
			tmpRD = new RegistrationData();
			tmpRD->InRegCmd = new KeyRegistrationCommand(this, argKey, argEv);
			tmpRD->InDerCmd = new KeyDeregistrationCommand(this, argKey, argEv);
			releaseMap.insert(std::pair<AZUL_KEY, RegistrationData*>(argKey, tmpRD));
		}
		else tmpRD = releaseMap.find(argKey)->second;

		assert(tmpRD->RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
		//SceneManager::GetCurrentScene()->SubmitCommand(tmpRD->InRegCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), tmpRD->InRegCmd);
		tmpRD->RegStateCurr = RegistrationState::PENDING_REGISTRATION;

		break;
	default:
		break;
	}
	
	

	
}

void Inputable::SubmitKeyDeregistration(AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	RegistrationData* tmpRD = pressMap.find(argKey)->second;;
	switch (argEv)
	{
	case KeyboardEventManager::KEY_PRESS:
		tmpRD = pressMap.find(argKey)->second;
		break;
	case KeyboardEventManager::KEY_RELEASE:
		tmpRD = releaseMap.find(argKey)->second;
		break;
	default:
		break;
	}

	
	assert(tmpRD->RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(tmpRD->InDerCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), tmpRD->InDerCmd);
	tmpRD->RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Inputable::SceneRegistration(AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	RegistrationData* tmpRD = pressMap.find(argKey)->second;;
	switch (argEv)
	{
	case KeyboardEventManager::KEY_PRESS:
		tmpRD = pressMap.find(argKey)->second;
		break;
	case KeyboardEventManager::KEY_RELEASE:
		tmpRD = releaseMap.find(argKey)->second;
		break;
	default:
		break;
	}

	assert(tmpRD->RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register(this, argKey, argEv);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this, argKey, argEv);
	tmpRD->RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(AZUL_KEY argKey, KeyboardEventManager::EVENT_TYPE argEv) {
	RegistrationData* tmpRD = pressMap.find(argKey)->second;;
	switch (argEv)
	{
	case KeyboardEventManager::KEY_PRESS:
		tmpRD = pressMap.find(argKey)->second;
		break;
	case KeyboardEventManager::KEY_RELEASE:
		tmpRD = releaseMap.find(argKey)->second;
		break;
	default:
		break;
	}

	assert(tmpRD->RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	//SceneManager::GetCurrentScene()->Deregister(this, argKey, argEv);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), this, argKey, argEv);
	tmpRD->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

Inputable::~Inputable() {
	std::multimap<AZUL_KEY, RegistrationData*>::const_iterator it;
	for (it = pressMap.begin(); it != pressMap.end(); ++it) {
		delete it->second->InRegCmd;
		delete it->second->InDerCmd;
		delete it->second;
	}
	for (it = releaseMap.begin(); it != releaseMap.end(); ++it) {
		delete it->second->InRegCmd;
		delete it->second->InDerCmd;
		delete it->second;
	}
}