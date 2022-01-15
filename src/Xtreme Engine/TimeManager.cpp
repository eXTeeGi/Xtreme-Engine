#include "TimeManager.h"
#include "XtremeEngine.h"
#include "FreezeTime.h"
#include "FreezeTimeAttorney.h"

TimeManager* TimeManager::ptrinstance;

TimeManager::TimeManager() {
	//FrzTime = new FreezeTime();
	FrzTime = FreezeTimeAttorney::newFreezeTime();
}

void TimeManager::Delete() {
	Instance().privDelete();
}

float TimeManager::GetFrameTime() {
	return Instance().privGetFrameTime();
}

float TimeManager::GetTime() {
	return Instance().privGetTime();
}

void TimeManager::ProcessTime(float arg) {
	Instance().privProcessTime(arg);
}

void TimeManager::privDelete() {
	//delete FrzTime;
	FreezeTimeAttorney::deleteFreezeTime(FrzTime);

	delete ptrinstance;
	ptrinstance = nullptr;
}

float TimeManager::privGetFrameTime() {
	return frameTime;
}

float TimeManager::privGetTime() {
	return currentTime;
}

void TimeManager::privProcessTime(float arg) {
	//currentTime = XtremeEngine::GetTime();
	//currentTime = FrzTime->GetTimeInSeconds(arg);
	currentTime = FreezeTimeAttorney::gTIS(FrzTime,arg);

	frameTime = currentTime - previousTime;

	previousTime = currentTime;
}