#include "AlarmableManager.h"
#include "Alarmable.h"
#include "AlarmableAttorney.h"
#include "XtremeEngine.h"
#include "TimeManager.h"

void AlarmableManager::Deregister( StorageMapRef& argRef) {
	StorageMapRef a = storageMap.erase(argRef);
}

void AlarmableManager::ProcessAlarms() {
	Alarmable* AL;
	AlarmEvent AE;
	ALARM_ID AID;
	while (!storageMap.empty() && storageMap.begin()->first <= TimeManager::GetTime()) {
		/*al = storageMap.begin()->second;
		al->TriggerAlarm();
		storageMap.erase(storageMap.begin()->first);*/

		AE = storageMap.begin()->second;
		AL = AE.first;
		AID = AE.second;

		storageMap.erase(storageMap.begin());
		//AL->TriggerAlarm(AID);
		AlarmableAttorney::Registration::TriggerAlarm(AID, AL);
		
		
	}
}

void AlarmableManager::Register(float argT, Alarmable* argA, ALARM_ID argAID, StorageMapRef& argRef) {
	//argRef = storageMap.insert(std::pair<float, Alarmable*>(argT, argA));
	argRef = storageMap.insert(std::pair<float, AlarmEvent>(argT, std::pair<Alarmable*, ALARM_ID>(argA, argAID)));
}

AlarmableManager::AlarmableManager() {

}

AlarmableManager::~AlarmableManager() {}
