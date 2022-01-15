#ifndef _Drawable
#define _Drawable

#include "DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
	friend class DrawableAttorney;
public:
	Drawable();
	 virtual ~Drawable();
	 Drawable(const Drawable&) = delete;
	 Drawable& operator=(const Drawable&) = delete;
	
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit registration for draw to be called. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitDrawRegistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit deregistration from draw being called. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitDrawDeregistration();

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};
	RegistrationState getRegState() { return RegStateCurr; };
private:
	virtual void Draw() {};
	virtual void Draw2D() {};
	void SceneRegistration();
	void SceneDeregistration();

	
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	DrawRegistrationCommand* DrRegCmd;
	DrawDeregistrationCommand* DrDerCmd;

	DrawableManager::StorageListRef pMyDeleteRef;
	
};

#endif _Drawable