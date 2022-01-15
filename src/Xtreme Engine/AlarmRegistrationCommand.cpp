#include "AlarmRegistrationCommand.h"
#include "Alarmable.h"
#include "AlarmableAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* argAl)
	: ptrAl(argAl)
{

}

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* argAl, AlarmableManager::ALARM_ID argID) 
	: ptrAl(argAl), al_id(argID)
{

}

void AlarmRegistrationCommand::execute() {
	//ptrAl->AlarmRegistration(t);
	AlarmableAttorney::Registration::AlarmRegistration(t, al_id,ptrAl);
}

void AlarmRegistrationCommand::setAlarmTime(float argT) {
	t = argT;
}

AlarmRegistrationCommand::~AlarmRegistrationCommand() {}