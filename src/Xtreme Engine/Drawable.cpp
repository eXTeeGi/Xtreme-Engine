#include "Drawable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "SceneAttorney.h"

Drawable::Drawable() {

	DrDerCmd = new DrawDeregistrationCommand(this);
	DrRegCmd = new DrawRegistrationCommand(this);
}

Drawable::~Drawable() {
	delete DrRegCmd;
	delete DrDerCmd;
}

void Drawable::SceneRegistration() {
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register(this, pMyDeleteRef);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this, pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration() {
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	//SceneManager::GetCurrentScene()->Deregister(pMyDeleteRef);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::SubmitDrawRegistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	//if (DrRegCmd == nullptr) DrRegCmd = new DrawRegistrationCommand(this);
	//SceneManager::GetCurrentScene()->SubmitCommand(DrRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), DrRegCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	//if (DrDerCmd == nullptr) DrDerCmd = new DrawDeregistrationCommand(this);
	//SceneManager::GetCurrentScene()->SubmitCommand(DrDerCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), DrDerCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}
