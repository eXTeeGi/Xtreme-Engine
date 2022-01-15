#include "AlarmDeregistrationCommand.h"
#include "Alarmable.h"
#include "AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* argAl)
	: ptrAl(argAl)
{

}

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* argAl, AlarmableManager::ALARM_ID argID)
	: ptrAl(argAl), al_id(argID)
{

}

void AlarmDeregistrationCommand::execute() {
	//ptrAl->AlarmDeregistration();
	AlarmableAttorney::Registration::AlarmDeregistration(al_id,ptrAl);
}

AlarmDeregistrationCommand::~AlarmDeregistrationCommand() {}