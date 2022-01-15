#include "SoundManager.h"

#include "SoundPlayerAttorney.h"

SoundManager* SoundManager::ptrinstance;

SoundManager::SoundManager() {
	
}

void SoundManager::Delete() {
	Instance().privDelete();
}

FMOD::Sound* SoundManager::Get2D(const string& argKey) {
	return Instance().privGet2D(argKey);
}

FMOD::Sound* SoundManager::Get3D(const string& argKey) {
	return Instance().privGet3D(argKey);
}


void SoundManager::Load2D(const string& argKey, const char* const argPath) {
	Instance().privLoad2D(argKey, argPath);
}

void SoundManager::Load3D(const string& argKey, const char* const argPath) {
	Instance().privLoad3D(argKey, argPath);
}

void SoundManager::privDelete() {

	//delete exInfo;

	delete ptrinstance;
	ptrinstance = nullptr;
}

FMOD::Sound* SoundManager::privGet2D(const string& argKey) {
	assert(SoundMap2D.find(argKey) != SoundMap2D.end() && (argKey + " Sound not loaded.").c_str());
	return SoundMap2D.find(argKey)->second;
}

FMOD::Sound* SoundManager::privGet3D(const string& argKey) {
	assert(SoundMap3D.find(argKey) != SoundMap3D.end() && (argKey + " Sound not loaded.").c_str());
	return SoundMap3D.find(argKey)->second;
}


void SoundManager::privLoad2D(const string& argKey, const char* const argPath) {
	assert(SoundMap2D.find(argKey) == SoundMap2D.end() && (argKey + " Sound loaded more than once.").c_str());
	FMOD::Sound* tmpSound;
	FMOD::System* system = SoundPlayerAttorney::Management::getSystem();
	FMOD_CREATESOUNDEXINFO* exInfo = SoundPlayerAttorney::Management::getExInfo();
	system->createSound(("Sounds/" + (string)argPath).c_str(), FMOD_DEFAULT, exInfo, &tmpSound);
	SoundMap2D[argKey] = tmpSound;
}

void SoundManager::privLoad3D(const string& argKey, const char* const argPath) {
	assert(SoundMap3D.find(argKey) == SoundMap3D.end() && (argKey + " Sound loaded more than once.").c_str());
	FMOD::Sound* tmpSound;
	FMOD::System* system = SoundPlayerAttorney::Management::getSystem();
	FMOD_CREATESOUNDEXINFO* exInfo = SoundPlayerAttorney::Management::getExInfo();
	system->createSound(("Sounds/" + (string)argPath).c_str(), FMOD_3D, exInfo, &tmpSound);
	SoundMap3D[argKey] = tmpSound;
}