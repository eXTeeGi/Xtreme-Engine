#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "SceneManager.h"
#include "CollidableGroup.h"
#include "SceneAttorney.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolume.h"

Collidable::Collidable() {

	pDeregCmd = new CollisionDeregistrationCommand(this);
	pRegCmd = new CollisionRegistrationCommand(this);
	ColVolume = nullptr;
	ColBSphere = new CollisionVolumeBSphere();
	ColAABB = new CollisionVolumeAABB();
	ColOBB = new CollisionVolumeOBB();
}

Collidable::~Collidable() {
	delete pDeregCmd;
	delete pRegCmd;
	delete ColBSphere;
	delete ColAABB;
	delete ColOBB;
}

void Collidable::SceneRegistration() {
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->GetCollisionManager()->GetColGroup(myID)->Register(this, pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration() {
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->GetCollisionManager()->GetColGroup(myID)->Deregister(pMyDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::SubmitCollisionRegistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pRegCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration() {
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pDeregCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::SetColliderModel(Model* mod, VolumeType VT) {
	pColModel = mod;

	switch (VT)
	{
	case Collidable::VolumeType::BSPHERE:
		ColVolume = ColBSphere;
		break;
	case Collidable::VolumeType::AABB:
		ColVolume = ColAABB;
		break;
	case Collidable::VolumeType::OBB:
		ColVolume = ColOBB;
		break;
	default:
		break;
	}

}

void Collidable::UpdateCollisionData(const Matrix& mat) {
	ColVolume->ComputeData(pColModel, mat);
	ColBSphere->ComputeData(pColModel, mat);
}

const CollisionVolume& Collidable::GetCollisionVolume() {
	return *ColVolume;
}

bool Collidable::isRegistered() {
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED) return true;
	else return false;
}

const CollisionVolume& Collidable::GetBSphere() {
	return *ColBSphere;
}