#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmDeregistrationCommand() = delete;
	~AlarmDeregistrationCommand();
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator= (const AlarmDeregistrationCommand&) = delete;

	AlarmDeregistrationCommand(Alarmable*);
	AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id);


	virtual void execute();
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;
	float al_time;
};

#endif _AlarmDeregistrationCommand