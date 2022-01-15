#include "Alarmable.h"
#include "Scene.h"
#include "SceneManager.h"
#include "AlarmRegistrationCommand.h"
#include "XtremeEngine.h"
#include "AlarmDeregistrationCommand.h"
#include "TimeManager.h"
#include "SceneAttorney.h"

Alarmable::Alarmable() {

	//AlDerCmd = new AlarmDeregistrationCommand(this);
	//AlRegCmd = new AlarmRegistrationCommand(this);

	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++) {
		RegData[i] = new RegistrationData();
		RegData[i]->AlRegCmd = new AlarmRegistrationCommand(this, (AlarmableManager::ALARM_ID)i);
		RegData[i]->AlDerCmd = new AlarmDeregistrationCommand(this, (AlarmableManager::ALARM_ID)i);
	}
}

Alarmable::~Alarmable() {
	//delete AlRegCmd;
	//delete AlDerCmd;

	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++) {
		delete RegData[i]->AlRegCmd;
		delete RegData[i]->AlDerCmd;
		delete RegData[i];
	}
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id) {
	//RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	RegData[id]->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	};

}

void Alarmable::AlarmRegistration(AlarmableManager::ALARM_ID argID, float t)
{
	assert(RegData[argID]->RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register(t, this, argID,RegData[argID]->pMyDeleteRef);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), t,this,argID, RegData[argID]->pMyDeleteRef);
	RegData[argID]->RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID argID)
{
	assert(RegData[argID]->RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	//SceneManager::GetCurrentScene()->Deregister(RegData[argID]->pMyDeleteRef);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), RegData[argID]->pMyDeleteRef);
	RegData[argID]->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID argID, float t)
{
	assert(RegData[argID]->RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	RegData[argID]->AlRegCmd->setAlarmTime(t + TimeManager::GetTime());
	//SceneManager::GetCurrentScene()->SubmitCommand(RegData[argID]->AlRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), RegData[argID]->AlRegCmd);
	RegData[argID]->RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID argID)
{
	assert(RegData[argID]->RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(RegData[argID]->AlDerCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), RegData[argID]->AlDerCmd);
	RegData[argID]->RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

Alarmable::RegistrationState Alarmable::getAlarmRegState(AlarmableManager::ALARM_ID argID) {
	return this->RegData[argID]->RegStateCurr;
}