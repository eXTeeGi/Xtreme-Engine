#include "SoundPlayer.h"

#include "SoundManager.h"
#include "XtremeMath.h"
#include "Collidable.h"
#include "CollisionVolumeBSphere.h"

SoundPlayer* SoundPlayer::ptrinstance;


SoundPlayer::SoundPlayer() {
	//FMOD
	FMOD_RESULT result;
	system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	exInfo = new FMOD_CREATESOUNDEXINFO();

	exInfo->cbsize = sizeof(FMOD_CREATESOUNDEXINFO);

	soundPos = new FMOD_VECTOR();
	soundVel = new FMOD_VECTOR();

	soundVel->x = 0;
	soundVel->y = 0;
	soundVel->z = 0;

	listenerPos = new FMOD_VECTOR();
	listenerVel = new FMOD_VECTOR();
	
	listenerVel->x = 0;
	listenerVel->y = 0;
	listenerVel->z = 0;

	listenerFor = new FMOD_VECTOR();
	listenerUp = new FMOD_VECTOR();

	Channel3D->setVolume(1.0f);

	listenerID = 0;
}

void SoundPlayer::Terminate() {
	Instance().privTerminate();

	delete ptrinstance;
	ptrinstance = nullptr;
}

void SoundPlayer::privTerminate() {
	delete exInfo;
	delete soundPos;
	delete soundVel;
	delete listenerPos;
	delete listenerVel;
	delete listenerFor;
	delete listenerUp;
}

void SoundPlayer::privUpdate() {
	system->update();
}

void SoundPlayer::privPlaySound(const string& argKey) {

	FMOD::Sound* sound = SoundManager::Get2D(argKey);

	Channel2D->setMode(FMOD_2D);

	system->playSound(sound, 0, false, &Channel2D);
	
}

void SoundPlayer::privPlaySound(const string& argKey, Vect& argPos) {

	FMOD::Sound* sound = SoundManager::Get3D(argKey);

	soundPos->x = argPos.X();
	soundPos->y = argPos.Y();
	soundPos->z = argPos.Z();

	Channel3D->setMode(FMOD_3D);
	Channel3D->set3DAttributes(soundPos, soundVel);

	float volume = 1.0f;

	//distance
	float tmp = XtremeMath::EuclideanNorm(listenerPosV - argPos) / 2000.0f;
	XtremeMath::Clamp(tmp,0.2f,1.0f);
	volume = 1.0f - tmp;

	//occlusion
	std::list<Collidable*>::iterator it;
	for (it = occludables.begin();it != occludables.end();++it) {
		Collidable* C = (*it);
		bool result = XtremeMath::Intersect(argPos,listenerPosV,(CollisionVolumeBSphere&)C->GetBSphere());
		if (result) {
			volume /= 5;
		}
	}

	system->playSound(sound, 0, false, &Channel3D);
	Channel3D->setVolume(volume);
}

void SoundPlayer::privListener(Vect argPos, Vect argFor, Vect argUp) {
	listenerPos->x = argPos.X();
	listenerPos->y = argPos.Y();
	listenerPos->z = argPos.Z();

	listenerFor->x = argFor.X();
	listenerFor->y = argFor.Y();
	listenerFor->z = argFor.Z();

	listenerUp->x = argUp.X();
	listenerUp->y = argUp.Y();
	listenerUp->z = argUp.Z();

	system->set3DListenerAttributes(listenerID++,listenerPos,listenerVel,listenerFor,listenerUp);
	if (listenerID > maxIDs) listenerID = 0;

	listenerPosV = argPos;
}

void SoundPlayer::privRegister(Collidable* arg) {
	occludables.push_back(arg);
}

void SoundPlayer::privDeregister(Collidable* arg) {
	occludables.remove(arg);
}