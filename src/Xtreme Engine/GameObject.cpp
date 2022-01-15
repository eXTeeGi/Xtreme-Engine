#include "GameObject.h"
#include "GameObjectExitCommand.h"
#include "GameObjectEntryCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneAttorney.h"

GameObject::GameObject() {
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
	pDeregCmd = new GameObjectExitCommand(this);
	pRegCmd = new GameObjectEntryCommand(this);
}

GameObject::~GameObject() {
	delete pRegCmd;
	delete pDeregCmd;
}

void GameObject::ConnectToScene() {
	assert(currState == RegistrationState::PENDING_REGISTRATION);

	this->SceneEntry(); // user method
	currState = RegistrationState::CURRENTLY_REGISTERED;
	

}

void GameObject::DisconnectFromScene() {
	assert(currState == RegistrationState::PENDING_DEREGISTRATION);

	this->SceneExit(); // user method
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameObject::SubmitEntry() {
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pRegCmd);
	currState = RegistrationState::PENDING_REGISTRATION;


}

void GameObject::SubmitExit() {
	assert(currState == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pDeregCmd);
	currState = RegistrationState::PENDING_DEREGISTRATION;
}

GameObject::RegistrationState GameObject::getRegState() {
	
	return currState;
}