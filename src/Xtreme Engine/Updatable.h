#ifndef _Updatable
#define _Updatable

#include "UpdatableManager.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
	friend class UpdatableAttorney;
private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called once per frame if the GameObject has been registered for updates.  </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Update() {};
	void SceneRegistration();
	void SceneDeregistration();

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	UpdateRegistrationCommand* UpRegCmd;
	UpdateDeregistrationCommand* UpDerCmd;
	
	UpdatableManager::StorageListRef pMyDeleteRef;
public:
	Updatable();
	virtual ~Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;
	
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit registration for update to be called. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitUpdateRegistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit deregistration from update being called. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitUpdateDeregistration();


};

#endif _Updatable