#ifndef _Inputable
#define _Inputable

#include "KeyboardEventManager.h"
#include <map>

class KeyRegistrationCommand;
class KeyDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;
private:

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};

	

	struct RegistrationData
	{
		//KeyboardEventManager::StorageMapRef pMyDeleteRef;
		RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		KeyRegistrationCommand* InRegCmd;
		KeyDeregistrationCommand* InDerCmd;
	};
	/*using RegMap = std::multimap<AZUL_KEY, RegistrationData*>;
	RegMap pressMap;
	RegMap releaseMap;*/

	std::multimap<AZUL_KEY, RegistrationData*> pressMap;
	std::multimap<AZUL_KEY, RegistrationData*> releaseMap;

	void SceneRegistration(AZUL_KEY, KeyboardEventManager::EVENT_TYPE);
	void SceneDeregistration(AZUL_KEY, KeyboardEventManager::EVENT_TYPE);
public:
	Inputable() = default;
	virtual ~Inputable();
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when a Key is pressed. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="parameter1">	The pressed key. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void KeyPressed(AZUL_KEY) {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when a Key is released. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="parameter1">	The released key. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void KeyReleased(AZUL_KEY) {};
	
	
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit a key's registration to the key input system. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="parameter1">	The key you want to register. </param>
	/// <param name="parameter2">	Whether you want to register a press or release. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitKeyRegistration( AZUL_KEY, KeyboardEventManager::EVENT_TYPE );

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit a key's deregistration from the key input system. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="parameter1">	The key you want to deregister. </param>
	/// <param name="parameter2">	Whether you want to deregister presses or releases. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitKeyDeregistration(AZUL_KEY, KeyboardEventManager::EVENT_TYPE);

	
};

#endif _Inputable