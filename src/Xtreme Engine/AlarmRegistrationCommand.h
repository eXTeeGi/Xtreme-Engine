#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"
class Alarmable;

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmRegistrationCommand() = delete;
	~AlarmRegistrationCommand();
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator= (const AlarmRegistrationCommand&) = delete;

	AlarmRegistrationCommand(Alarmable*);
	AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id);

	virtual void execute();
	void setAlarmTime(float);

	//Alarmable* ptrAl;
	float t;
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;
	float al_time;

};

#endif _AlarmRegistrationCommand