#ifndef _Alarmable
#define _Alarmable

#include "AlarmableManager.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;
public:
	Alarmable();
	~Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator= (const Alarmable&) = delete;
	

	
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit alarm registration. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="ALARM_ID">	The alarm you want to set. </param>
	/// <param name="float">	Time in seconds before alarm triggers. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SubmitAlarmRegistration(AlarmableManager::ALARM_ID, float);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit alarm deregistration. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="ALARM_ID">	The alarm you want to cancel. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID);

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};
private:

	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when Alarm 0 triggers. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm0() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when Alarm 1 triggers. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm1() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when Alarm 2 triggers. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm2() {};

	void AlarmRegistration(AlarmableManager::ALARM_ID, float);
	void AlarmDeregistration(AlarmableManager::ALARM_ID);

	
	/*RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	AlarmRegistrationCommand* AlRegCmd;
	AlarmDeregistrationCommand* AlDerCmd;

	AlarmableManager::StorageMapRef pMyDeleteRef;*/

	struct RegistrationData
	{
		AlarmableManager::StorageMapRef pMyDeleteRef;
		RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		AlarmRegistrationCommand* AlRegCmd;
		AlarmDeregistrationCommand* AlDerCmd;
	};

	RegistrationData* RegData[AlarmableManager::ALARM_NUMBER];
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the registration state of an alarm. </summary>
	///
	/// <remarks>	Jakei, 3/6/2020. </remarks>
	///
	/// <param name="id">	The Alarm ID </param>
	///
	/// <returns>	The alarm registration state. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	RegistrationState getAlarmRegState(AlarmableManager::ALARM_ID id);
};

#endif _Alarmable