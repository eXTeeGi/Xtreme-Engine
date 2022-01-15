#include "Updatable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "SceneAttorney.h"

Updatable::Updatable() {
	
	UpDerCmd = new UpdateDeregistrationCommand(this);
	UpRegCmd = new UpdateRegistrationCommand(this);
}

Updatable::~Updatable() {
	delete UpRegCmd;
	delete UpDerCmd;
}

void Updatable::SceneRegistration() {
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register( this, pMyDeleteRef);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this, pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration() {
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	//SceneManager::GetCurrentScene()->Deregister(pMyDeleteRef);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updatable::SubmitUpdateRegistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	//if (UpRegCmd == nullptr) UpRegCmd = new UpdateRegistrationCommand(this);
	//SceneManager::GetCurrentScene()->SubmitCommand(UpRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), UpRegCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	//if (UpDerCmd == nullptr) UpDerCmd = new UpdateDeregistrationCommand(this);
	//SceneManager::GetCurrentScene()->SubmitCommand(UpDerCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), UpDerCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}