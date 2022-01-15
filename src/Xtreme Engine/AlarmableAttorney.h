#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
		friend class AlarmableManager;
	private:
		static void AlarmRegistration(float t,AlarmableManager::ALARM_ID argID,Alarmable* pMgr) { pMgr->AlarmRegistration(argID,t); }
		static void AlarmDeregistration(AlarmableManager::ALARM_ID argID, Alarmable* pMgr) { pMgr->AlarmDeregistration(argID); }
		static void TriggerAlarm(AlarmableManager::ALARM_ID id, Alarmable* pMgr) { pMgr->TriggerAlarm(id); };
	};
};


#endif _AlarmableAttorney